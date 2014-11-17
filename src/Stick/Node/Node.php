<?hh

namespace Stick\Node;

abstract class Node
{
  protected array<Base> $nodes;

  public function getChildren(): array<Node> {
    return $this->nodes;
  }
}
