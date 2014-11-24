<?hh

namespace Stick\Node;

use Stick\Token;

class ForLoop extends Node
{
    public function __construct(private Token $array, private Token $value) {}
    // TODO
    public function isBlockEnd(Token $token) : bool
    {
        return ($token->getValue() === "endfor");
    }
}
