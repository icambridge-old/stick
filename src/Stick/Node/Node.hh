<?hh

namespace Stick\Node;

abstract class Node
{
    protected Vector<Node> $nodes = [];

    public function addNode(Node $node): void {
        $this->nodes[] = $node;
    }

    public function getChildren(): Vector<Node> {
        return $this->nodes;
    }
}
