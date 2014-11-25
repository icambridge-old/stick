<?hh

namespace Stick;

use HackPack\HackUnit\Core\Expectation;
use HackPack\HackUnit\Core\TestCase;

class VariableContainerTest extends TestCase
{
    public function testSetAndGet(): void
    {
        $key = "hello";
        $value = "world";

        $container = new VariableContainer();
        $container->set($key, $value);
        $this->expect($container->get($key))->toEqual($value);
    }
}
