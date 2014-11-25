<?hh

namespace Stick\Node;

use HackPack\HackUnit\Core\Expectation;
use HackPack\HackUnit\Core\TestCase;
use Stick\VariableContainer;
use Stick\Token;

class ForLoopTest extends TestCase
{
    public function testCompiles(): void {
        $variableName = "variableName";
        $text = "helloworld";

        $node = new Variable(new Token(Token::TYPE_NAME, $variableName));
        $forLoop = new ForLoop(new Token(Token::TYPE_NAME, "array"), new Token(Token::TYPE_NAME, $variableName));
        $forLoop->addNode($node);

        $container = new VariableContainer();
        $container->set("array", ["hello", "world"]);

        $this->expect($forLoop->compile($container))->toEqual($text);
    }
}
