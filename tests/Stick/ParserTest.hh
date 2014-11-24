<?hh

namespace Stick;

use HackPack\HackUnit\Core\Expectation;
use HackPack\HackUnit\Core\TestCase;

class ParserTest extends TestCase
{
  public function testReturnsTextNode(): void {
    $textValue = "Hello World";
    $tokens = new TokenCollection();
    $tokens->add(new Token(Token::TYPE_TEXT, $textValue));
    $tokens->add(new Token(Token::TYPE_EOF, ""));

    $parser = new Parser();
    $nodes = $parser->parse($tokens)->getChildren();

    $this->expect(is_a($nodes[0], '\\Stick\\Node\\Text'))->toEqual(true);
  }

  public function testReturnsVariableNode(): void {

      $tokens = new TokenCollection();
      $tokens->add(new Token(Token::TYPE_VARIABLE_START, ""));
      $tokens->add(new Token(Token::TYPE_NAME, "helloWorld"));
      $tokens->add(new Token(Token::TYPE_VARIABLE_END, ""));
      $tokens->add(new Token(Token::TYPE_EOF, ""));

      $parser = new Parser();
      $nodes = $parser->parse($tokens)->getChildren();
      $this->expect(is_a($nodes[0], '\\Stick\\Node\\Write'))->toEqual(true);
  }

  public function testReturnsVariableNodeWithVariableNameInside(): void {

      $tokens = new TokenCollection();
    $tokens->add(new Token(Token::TYPE_VARIABLE_START, ""));
    $tokens->add(new Token(Token::TYPE_NAME, "helloWorld"));
    $tokens->add(new Token(Token::TYPE_VARIABLE_END, ""));
    $tokens->add(new Token(Token::TYPE_EOF, ""));

    $parser = new Parser();
    $nodes = $parser->parse($tokens)->getChildren();
    $children = $nodes[0]->getChildren();
    $this->expect(is_a($children[0], '\\Stick\\Node\\Variable'))->toEqual(true);
  }

  public function testReturnsForLoopNode(): void {

    $tokens = new TokenCollection();
    $tokens->add(new Token(Token::TYPE_BLOCK_START, ""));
    $tokens->add(new Token(Token::TYPE_NAME, "for"));
    $tokens->add(new Token(Token::TYPE_NAME, "var"));
    $tokens->add(new Token(Token::TYPE_OPERATOR, "in"));
    $tokens->add(new Token(Token::TYPE_NAME, "array"));
    $tokens->add(new Token(Token::TYPE_BLOCK_END, ""));
    $tokens->add(new Token(Token::TYPE_EOF, ""));

    $parser = new Parser();
    $nodes = $parser->parse($tokens)->getChildren();
    $this->expect(is_a($nodes[0], '\\Stick\\Node\\ForLoop'))->toEqual(true);
  }

}
