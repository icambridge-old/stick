<?hh //strict

namespace Stick;

class Lexer
{
    const STATE_TEXT = 0;
    const STATE_BLOCK = 1;
    const STATE_VARIABLE = 2;

    const TAG_BLOCK_OPEN = '{%';
    const TAG_BLOCK_CLOSE = '%}';
    const TAG_COMMENT_OPEN = '{#';
    const TAG_COMMENT_CLOSE = '#}';
    const TAG_VARIABLE_OPEN = '{{';
    const TAG_VARIABLE_CLOSE = '}}';


    private string $template = "";
    private int $end = 0;
    private int $cursor = 0;
    private int $position = -1;
    private int $state = 0;
    private array<array<string>> $positions = [];
    private array<Token> $tokens = [];

    public function tokenize(string $template): array<Token> {
        $this->template = $template;
        $this->process($template);
        $this->tokens[] = new Token(Token::TYPE_EOF, '');
        return $this->tokens;
    }

    public function process(string $template): array<Token> {
        $tagOpenRegex = '~('.preg_quote(self::TAG_VARIABLE_OPEN, '/') .
                 '|'.preg_quote(self::TAG_BLOCK_OPEN, '/') .
                 '|'.preg_quote(self::TAG_COMMENT_OPEN, '/') .')~s';
        $matches = [];
        preg_match_all($tagOpenRegex, $template, $matches, \PREG_OFFSET_CAPTURE);

        $this->positions = $matches;
        $this->end = strlen($template);

        do {
          switch ($this->state){
            case self::STATE_TEXT:
              $this->processText();
              break;
            case self::STATE_BLOCK:
              $this->processBlock();
              break;
            case self::STATE_VARIABLE:
              $this->processVariable();
              break;
          }


        } while ($this->cursor < $this->end);

        if ($this->state != self::STATE_TEXT) {
            throw new Exception\InvalidSyntax("Unended block");
        }


        return $this->tokens;
    }

    private function processText(): void
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
        $text = substr($this->template, $this->cursor, intval($currentPosition[1]) - $this->cursor);


        $this->pushToken(Token::TYPE_TEXT, $text);

        $this->moveCursor($text.$currentPosition[0]);

        if ($currentPosition[0] == self::TAG_BLOCK_OPEN) {
          $this->pushToken(Token::TYPE_BLOCK_START);
          $this->setState(self::STATE_BLOCK);
          $this->processBlock();
        } elseif ($currentPosition[0] == self::TAG_VARIABLE_OPEN) {
          $this->pushToken(Token::TYPE_VARIABLE_START);
          $this->setState(self::STATE_VARIABLE);
          $this->processVariable();
        } elseif ($currentPosition[0] == self::TAG_COMMENT_OPEN) {
          $matches = [];
          if (!preg_match("~.*".preg_quote(self::TAG_COMMENT_CLOSE)."~A", $this->template, $matches, null, $this->cursor)) {
              throw new Exception\InvalidSyntax("Unfinished comment");
          }
          $this->moveCursor($matches[0]);
        }

    }

    private function endIt(): void
    {
        $this->cursor = $this->end;
    }

    private function processBlock(): void
    {
        $match = [];
        $regexBlockEnd = "~".preg_quote(self::TAG_BLOCK_CLOSE)."~A";
        if (preg_match($regexBlockEnd, $this->template, $match, null, $this->cursor)) {
          $this->pushToken(Token::TYPE_BLOCK_END);
          $this->moveCursor($match[0]);
          $this->setState(self::STATE_TEXT);
        } else {
          $this->processExpression();
        }
    }

    private function processVariable(): void
    {
        $regexBlockEnd = "~".preg_quote(self::TAG_VARIABLE_CLOSE)."~A";
        $match = [];
        if (preg_match($regexBlockEnd, $this->template, $match, null, $this->cursor)) {
          $this->pushToken(Token::TYPE_VARIABLE_END);
          $this->moveCursor($match[0]);
          $this->setState(self::STATE_TEXT);
        } else {
          $this->processExpression();
        }
    }

    private function processExpression(): void
    {

        $regexName = "~[a-z0-9_][a-z0-9_]*~A";

        $this->ignoreWhitespace();
        $match = [];
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
      $match = [];
      if (preg_match('/\s+/A', $this->template, $match, null, $this->cursor)) {
        $this->moveCursor($match[0]);

        if ($this->cursor >= $this->end) {
          throw new Exception\InvalidSyntax("Missing %}");
        }
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
        if ($text == "" && Token::TYPE_TEXT == $type) {
          return;
        }

        $this->tokens[] = new Token($type, $text);
    }
}
