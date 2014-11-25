<?hh //strict

namespace Stick;

use Stick\Exception\InvalidSyntax;

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
                $this->generateBlockNode();
                break;
              default:
                break;
        }
        $token = $tokens->getNext();
      } while ($token->getType() != Token::TYPE_EOF);

      if ($this->currentNode !== $this->baseNode) {
          // TODO which block it is to $this->currentNode;
          throw new InvalidSyntax("Didn't close block");
      }

      return $this->baseNode;
    }

    private function endBlock($token): void
    {
        $endBlock = $this->tokens->getNext();
        if (!$endBlock->isEndBlock()) {
            $exceptionMessage = sprintf("excepted end of block not %s", $endBlock->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        if (!$this->currentNode->isBlockEnd($token)) {
            throw new InvalidSyntax("Not correct block ending");
        }

        $currentNode = $this->currentNode->getParent();
        $this->currentNode = $currentNode;
    }

    // TODO refactor out into seperate class. Again.
    // TOOD Factory
    private function startBlock(): void
    {
        $value = $this->tokens->getNext();

        if (!$value->isName()) {
            $exceptionMessage = sprintf("excepted value name not %s", $value->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $operator = $this->tokens->getNext();

        if (!$operator->isOperator()) {
            $exceptionMessage = sprintf("excepted operator not %s", $operator->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $array = $this->tokens->getNext();

        if (!$array->isName()) {
            $exceptionMessage = sprintf("excepted array not %s", $array->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $endBlock = $this->tokens->getNext();
        if (!$endBlock->isEndBlock()) {
            $exceptionMessage = sprintf("excepted end of block not %s", $endBlock->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $node =  new Node\ForLoop($array, $value);
        $this->currentNode->addNode($node);
        $this->currentNode = $node;
    }

    private function generateBlockNode(): void
    {
        $blockName = $this->tokens->getNext();


        if (!$this->isStartNode($blockName) && !$this->isEndNode($blockName)) {
            $exceptionMessage = sprintf("'%s' isn't a valid block name", $blockName->getValue());
            throw new InvalidSyntax($exceptionMessage);
        }

        if ($this->isStartNode($blockName)) {
            return $this->startBlock();
        }

        if ($this->isEndNode($blockName)) {
            return $this->endBlock($blockName);
        }
    }

    private function generateVariableNode(Token $token): Node\Node
    {
        $name = $this->tokens->getNext();
        if (!$name->isName()) {
            $exceptionMessage = sprintf("excepted value name not %s", $value->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $variableEnd = $this->tokens->getNext();
        if (!$variableEnd->isVariableEnd()) {
            $exceptionMessage = sprintf("excepted variable end %s", $value->getType());
            throw new InvalidSyntax($exceptionMessage);
        }


        return new Node\Write(new Node\Variable($name));
    }

    // TODO move to dependency
    private function isStartNode($token): bool
    {
        $vector = Vector{"for"};
        return ($vector->linearSearch($token->getValue()) !== -1);
    }

    private function isEndNode($token): bool
    {
        $vector = Vector{"endfor", "endif"};
        return ($vector->linearSearch($token->getValue()) !== -1);
    }
}
