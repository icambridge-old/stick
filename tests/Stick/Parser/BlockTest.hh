<?hh

namespace Stick\Parser;

use HackPack\HackUnit\Core\Expectation;
use HackPack\HackUnit\Core\TestCase;
use Stick\TokenCollection;
use Stick\Token;

class BlockTest extends TestCase
{
    public function testThrowsExceptionIfInvalidBlockName(): void
    {
        $subParser = new Block();
        $tokenCollection = new TokenCollection();
        $tokenCollection->add(new Token(Token::TYPE_NAME, "batman"));
        $this->expectCallable(() ==> {$subParser->parse($tokenCollection);})->toThrow("Stick\\Exception\\InvalidSyntax");
    }

    public function testThrowsExceptionIfBlockEndedTooSoon(): void
    {
        $subParser = new Block();
        $tokenCollection = new TokenCollection();
        $tokenCollection->add(new Token(Token::TYPE_NAME, "for"));
        $tokenCollection->add(new Token(Token::TYPE_BLOCK_END, ""));
        $this->expectCallable(() ==> {$subParser->parse($tokenCollection);})->toThrow("Stick\\Exception\\InvalidSyntax");
    }

    private function getTokenCollection() : TokenCollection
    {
        $tokenCollection = new TokenCollection();
        $tokenCollection->add(new Token(Token::TYPE_NAME, "for"));
        $tokenCollection->add(new Token(Token::TYPE_NAME, "var"));
        $tokenCollection->add(new Token(Token::TYPE_OPERATOR, "in"));
        $tokenCollection->add(new Token(Token::TYPE_NAME, "array"));
        $tokenCollection->add(new Token(Token::TYPE_BLOCK_END, ""));
        return $tokenCollection;
    }
}
