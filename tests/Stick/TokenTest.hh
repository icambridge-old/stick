<?hh

namespace Stick;

use HackPack\HackUnit\Core\Expectation;
use HackPack\HackUnit\Core\TestCase;

class TokenTest extends TestCase
{
    public function testGetType(): void
    {
        $type = 'Comment';
        $token = new Token($type, 'Stuff');
        $this->expect($token->getType())->toEqual($type);
    }
}
