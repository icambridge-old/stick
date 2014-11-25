<?hh

namespace Stick\Node;

use HackPack\HackUnit\Core\Expectation;
use HackPack\HackUnit\Core\TestCase;
use Stick\VariableContainer;

class TextTest extends TestCase
{
    public function testCompileReturnsText(): void
    {
        $text = "Hello world";
        $node = new Text($text);
        $container = new VariableContainer();
        $this->expect($node->compile($container))->toEqual($text);
    }
}
