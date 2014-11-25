<?hh

namespace Stick\Node;

use HackPack\HackUnit\Core\Expectation;
use HackPack\HackUnit\Core\TestCase;
use Stick\VariableContainer;
use Stick\Token;

class VariableTest extends TestCase
{
    public function testCompileReturnsText(): void
    {
        $variableName = "variableName";
        $text = "hello";
        $node = new Variable(new Token(Token::TYPE_NAME, $variableName));
        $container = new VariableContainer();
        $container->set($variableName, $text);
        $this->expect($node->compile($container))->toEqual($text);
    }
}
