<?hh

namespace Stick\Node;

class Text extends Node
{
    public function __construct(private string $value){}

    public function output(): string
    {
      return $this->value;
    }
}
