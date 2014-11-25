<?hh

namespace Stick\Node;

use Stick\Token;
use Stick\VariableContainer;

class ForLoop extends Node
{
    public function __construct(private Token $array, private Token $value) {}

    public function compile(VariableContainer $container): string
    {
        $output = "";
        $array = $container->get($this->array->getValue());

        foreach ($array as $arrayValue) {
            $container->set($this->value->getValue(), $arrayValue);
            foreach ($this->nodes as $node) {
                $output .= $node->compile($container);
            }
        }

        return $output;
    }

    public function isBlockEnd(Token $token) : bool
    {
        return ($token->getValue() === "endfor");
    }
}
