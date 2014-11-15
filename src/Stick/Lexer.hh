<?hh //strict

namespace Iain\Framework\Template;

class Lexer
{
    const STATE_DATA = 0;
    const STATE_BLOCK = 1;
    const STATE_VARIABLE = 2;


    private string $template;
    private int $cursor = 0;
    private int $position = -1;
    private int $state = 0;
    private array $positons = [];
    private array $tokens = [];

    public function tokenize(string $template): array {
        $this->template = $template;
        $this->process($template);
        $this->tokens[] = new Token(Token::TYPE_EOF, '');
        return $this->tokens;
    }

    public function process(string $template) {
        $regex = '/('.preg_quote('{{', '/').'|'.preg_quote('{%', '/').'|'.preg_quote('{#', '/').')/s';
        preg_match_all($regex, $template, $matches, PREG_OFFSET_CAPTURE);

        $this->positions = $matches;
        $this->end = strlen($template);

        do {
          switch ($this->state){
            case self::STATE_DATA:
              $this->processData();
              break;
            case self::STATE_BLOCK:
              $this->processBlock();
              break;
            case self::STATE_VARIABLE:
              $this->processVariable();
              break;
          }


        } while ($this->cursor < $this->end);


        return $this->tokens;
    }

    private function processData()
    {
       if ($this->position == count($this->positions[0]) - 1) {
            $string = substr($this->template, $this->cursor);
            $this->pushToken(Token::TYPE_TEXT, "$string");
            $this->cursor = $this->end;
            return;
        }

        $this->position++;
        $currentPosition = $this->positions[0][$this->position];


        // push the template text first
        $rawText = $text = substr($this->template, $this->cursor, $currentPosition[1] - $this->cursor);
        if (isset($this->positions[2][$this->position][0])) {
            $text = rtrim($rawText);
        }
        $this->pushToken(Token::TYPE_TEXT, $text);
        $this->moveCursor($text.$currentPosition[0]);
        if ($currentPosition[0] == '{%') {
          $this->pushToken(Token::TYPE_BLOCK_START);
          $this->setState(self::STATE_BLOCK);
          $this->processBlock();
        } elseif ($currentPosition[0] == "{{") {
          $this->pushToken(Token::TYPE_VARIABLE_START);
          $this->setState(self::STATE_VARIABLE);
          $this->processVariable();
        } else {
          $this->endIt();
        }


        return;

    }

    private function endIt(): void
    {
        $this->cursor = $this->end;
    }

    private function processBlock(): void
    {
        $regexBlockEnd = "~".preg_quote("%}")."~A";
        if (preg_match($regexBlockEnd, $this->template, $match, null, $this->cursor)) {
          $this->pushToken(Token::TYPE_BLOCK_END);
          $this->moveCursor($match[0]);
          $this->setState(self::STATE_DATA);
        } else {
          $this->processExpression();
        }
    }

    private function processVariable(): void
    {
        $regexBlockEnd = "~".preg_quote("}}")."~A";
        if (preg_match($regexBlockEnd, $this->template, $match, null, $this->cursor)) {
          $this->pushToken(Token::TYPE_VARIABLE_END);
          $this->moveCursor($match[0]);
          $this->setState(self::STATE_DATA);
        } else {
          $this->processExpression();
        }
    }

    private function processExpression(): void
    {

        $regexName = "~[a-z0-9_][a-z0-9_]*~A";

        $this->ignoreWhitespace();
        if (preg_match('~in~iA', $this->template, $match, null, $this->cursor)) {
          $this->pushToken(Token::TYPE_OPERATOR, $match[0]);
          $this->moveCursor($match[0]);
        } elseif (preg_match($regexName, $this->template, $match, null, $this->cursor)) {
          $this->pushToken(Token::TYPE_NAME, $match[0]);
          $this->moveCursor($match[0]);
        }
    }

    private function ignoreWhitespace(): void
    {
      if (preg_match('/\s+/A', $this->template, $match, null, $this->cursor)) {
        $this->moveCursor($match[0]);
      }
    }


    private function setState(int $state): void
    {
        $this->state = $state;
    }

    private function moveCursor(string $string): void
    {
        $this->cursor += strlen($string);
    }

    private function pushToken(string $type, string $text = ''): void
    {
        $this->tokens[] = new Token($type, $text);
    }
}
