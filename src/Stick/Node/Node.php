<?hh

namespace Stick\Node;

abstract class Node
{
  protected array<Node> $nodes = [];

  public function getChildren(): array<Node> {
    return $this->nodes;
  }
}
