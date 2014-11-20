<?hh

namespace Stick;

use HackPack\HackUnit\Core\Expectation;
use HackPack\HackUnit\Core\TestCase;

class ParserTest extends TestCase
{
  public function testReturnsTextNode(): void {
    $textValue = "Hello World";
    $tokens = [];
    $tokens[] = new Token(Token::TYPE_TEXT, $textValue);
    $tokens[] = new Token(Token::TYPE_EOF, "");

    $parser = new Parser();
    $nodes = $parser->parse($tokens);

    $this->expect(is_a($nodes[0], '\\Stick\\Node\\Text'))->toEqual(true);
  }

  public function testReturnsVariableNode(): void {

    $tokens = [];
    $tokens[] = new Token(Token::TYPE_VARIABLE_START, "");
    $tokens[] = new Token(Token::TYPE_NAME, "helloWorld");
    $tokens[] = new Token(Token::TYPE_VARIABLE_END, "");
    $tokens[] = new Token(Token::TYPE_EOF, "");

    $parser = new Parser();
    $nodes = $parser->parse($tokens);
    $this->expect(is_a($nodes[0], '\\Stick\\Node\\Write'))->toEqual(true);
  }

  public function testReturnsVariableNodeWithVariableNameInside(): void {

    $tokens = [];
    $tokens[] = new Token(Token::TYPE_VARIABLE_START, "");
    $tokens[] = new Token(Token::TYPE_NAME, "helloWorld");
    $tokens[] = new Token(Token::TYPE_VARIABLE_END, "");
    $tokens[] = new Token(Token::TYPE_EOF, "");

    $parser = new Parser();
    $nodes = $parser->parse($tokens);
    $children = $nodes[0]->getChildren();
    $this->expect(is_a($children[0], '\\Stick\\Node\\Variable'))->toEqual(true);
  }

  public function testReturnsForLoopNode(): void {

    $tokens = [];
    $tokens[] = new Token(Token::TYPE_BLOCK_START, "");
    $tokens[] = new Token(Token::TYPE_NAME, "for");
    $tokens[] = new Token(Token::TYPE_NAME, "var");
    $tokens[] = new Token(Token::TYPE_OPERATOR, "in");
    $tokens[] = new Token(Token::TYPE_NAME, "array");
    $tokens[] = new Token(Token::TYPE_BLOCK_END, "");
    $tokens[] = new Token(Token::TYPE_EOF, "");

    $parser = new Parser();
    $nodes = $parser->parse($tokens);
    $this->expect(is_a($nodes[0], '\\Stick\\Node\\ForLoop'))->toEqual(true);
  }
}
