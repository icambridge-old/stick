<?hh //strict

namespace Stick\Parser;

use Stick\Node\Node;
use Stick\TokenCollection;
use Stick\Token;
use Stick\Exception\InvalidSyntax;

class Block
{
    public function parse(TokenCollection $tokenCollection): Node
    {
        $blockName = $tokenCollection->next();

        if ($blockName->getValue() !== "for") {
            $exceptionMessage = sprintf("'%s' isn't a valid block name", $blockName->getValue());
            throw new InvalidSyntax($exceptionMessage);
        }

        $value = $tokenCollection->next();

        if (!$value->isName()) {
            $exceptionMessage = sprintf("excepted value name not %s", $blockName->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $operator = $tokenCollection->next();

        if (!$operator->isOperator()) {
            $exceptionMessage = sprintf("excepted operator not %s", $blockName->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $array = $tokenCollection->next();

        if (!$array->isName()) {
            $exceptionMessage = sprintf("excepted array not %s", $blockName->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        $endBlock = $tokenCollection->next();
        if (!$endBlock->isEndBlock()) {
            $exceptionMessage = sprintf("excepted end of block not %s", $blockName->getType());
            throw new InvalidSyntax($exceptionMessage);
        }

        return new ForLoop($array, $value);
    }

    private function isName(Token $token): bool
    {
        return $token->getType() == Token::TYPE_NAME;
    }
}
