<?hh //strict

namespace Stick\Parser;

use Stick\Node\Node;
use Stick\Node\ForLoop;
use Stick\TokenCollection;
use Stick\Token;
use Stick\Exception\InvalidSyntax;

class Block
{
    public function parse(TokenCollection $tokenCollection): Node
    {
        $blockName = $tokenCollection->getNext();

        if ($blockName->getValue() !== "for") {
            $exceptionMessage = sprintf("'%s' isn't a valid block name", $blockName->getValue());
            throw new InvalidSyntax($exceptionMessage);
        }

        $value = $tokenCollection->getNext();

        if (!$value->isName()) {
            $exceptionMessage = sprintf("excepted value name not %s", $value->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $operator = $tokenCollection->getNext();

        if (!$operator->isOperator()) {
            $exceptionMessage = sprintf("excepted operator not %s", $operator->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $array = $tokenCollection->getNext();

        if (!$array->isName()) {
            $exceptionMessage = sprintf("excepted array not %s", $array->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $endBlock = $tokenCollection->getNext();
        if (!$endBlock->isEndBlock()) {
            $exceptionMessage = sprintf("excepted end of block not %s", $endBlock->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        return new ForLoop($array, $value);
    }

    private function isName(Token $token): bool
    {
        return $token->getType() == Token::TYPE_NAME;
    }
}
