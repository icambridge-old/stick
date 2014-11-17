<?hh

namespace Stick\Node;

use HackPack\HackUnit\Core\Expectation;
use HackPack\HackUnit\Core\TestCase;

class TextTest extends TestCase
{
    public function testReturnsOutput(): void
    {
        $node = new Text("Hello World");
        $this->expect($node->output())->toEqual("Hello World");
    }
}
