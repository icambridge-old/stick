<?hh

namespace Stick\Node;

class Write extends Node
{
    public function __construct(Node $node){
        $this->nodes[] = $node;
    }
}
