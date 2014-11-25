<?hh

namespace Stick\Node;

use Stick\VariableContainer;
use Stick\Token;

class Variable extends Node
{
    public function __construct(private Token $variable) {}


    public function compile(VariableContainer $container): string {
        return $container->get($this->variable->getValue());
    }
}
