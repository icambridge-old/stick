<?hh

namespace Stick\Node;

use Stick\VariableContainer;
use Stick\Token;

abstract class Node
{
    protected Vector<Node> $nodes = Vector{};

    private ?Node $parent;

    public function addParent(Node $node) : void {
        $this->parent = $node;
    }

    public function getParent(): Node {
        if ($this->parent === null) {
            throw new \Exception("Rename this exception - No parent found");
        }

        return $this->parent;
    }

    public function compile(VariableContainer $container): string {
        return "";
    }

    public function addNode(Node $node): void {
        $node->addParent($this);
        $this->nodes[] = $node;
    }

    public function getChildren(): Vector<Node> {
        return $this->nodes;
    }

    public function isBlockEnd(Token $token) : bool
    {
        return false;
    }
}
