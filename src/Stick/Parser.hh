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
        $this->currentNode = $this->baseNode = new Node\Base();
    }

    public function parse(TokenCollection $tokens): Node\Node
    {
      $output = [];
      $this->tokens = $tokens;
      $token = $tokens->getNext();
      do {
          switch($token->getType()) {
              case Token::TYPE_TEXT:
                $this->currentNode->addNode(new Node\Text($token->getValue()));
                break;
              case Token::TYPE_VARIABLE_START:
                $this->currentNode->addNode($this->generateVariableNode($token));
                break;
              case Token::TYPE_BLOCK_START:
                $blockNode = $this->generateBlockNode();
                $this->currentNode->addNode($blockNode);
                $this->currentNode = $blockNode;
                break;
              default:
                break;
        }
        $token = $tokens->getNext();
      } while ($token->getType() != Token::TYPE_EOF);

      return $this->baseNode;
    }

    private function generateBlockNode(): Node\Node
    {
        $parser = new Parser\Block();
        $node = $parser->parse($this->tokens);

        return $node;
    }

    private function generateVariableNode(Token $token): Node\Node
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
