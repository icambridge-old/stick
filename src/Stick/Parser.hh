<?hh //strict

namespace Stick;

class Parser
{
    private int $counter = 0;
    private array<Token> $tokens;

    public function parse(array<Token> $tokens): array
    {
      $output = [];
      $this->tokens = $tokens;
      while ($token = $this->getNextToken()) {
        switch($token->getType()) {
          case Token::TYPE_TEXT:
            $output[] = new Node\Text($token->getValue());
            break;
          case Token::TYPE_VARIABLE_START:
            $output[] = $this->generateVariableNode($token);
          default:
            break;
        }
      }

      return $output;
    }

    public function generateVariableNode(Token $token): Node\Node
    {
      return new Node\Write(new Node\Variable());
    }

    // TODO Move to collection
    private function getNextToken(): ?Token
    {
      if (!isset($this->tokens[$this->counter])) {
        return null;
      }

      return $this->tokens[$this->counter++];
    }
}
