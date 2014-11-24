<?hh //strict

namespace Stick;

class Parser
{
    private int $counter = 0;
    private array<Token> $tokens = [];
    private Node $baseNode;
    private Node $currentNode;

    public function __construct() : void
    {
        $this->currentNode = $this->baseName = new Node\Base();
    }

    public function parse(array<Token> $tokens): array<Node\Node>
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
            break;
          case Token::TYPE_BLOCK_START:
            $output[] = $this->generateBlockNode($token);
            break;
          default:
            break;
        }
      }

      return $output;
    }

    public function generateBlockNode(Token $token): Node\Node
    {
        $node = new Node\ForLoop();

        return $node;
    }

    public function generateVariableNode(Token $token): Node\Node
    {
      return new Node\Write(new Node\Variable());
    }

    // TODO Move to collection
    private function getNextToken(): ?Token
    {
      if (!array_key_exists($this->counter ,$this->tokens)) {
        return null;
      }

      return $this->tokens[$this->counter++];
    }
}
