<?hh

namespace Stick\Node;

use Stick\VariableContainer;

class Text extends Node
{
    public function __construct(private string $value){}

    public function compile(VariableContainer $container): string
    {
        return $this->value;
    }
}
