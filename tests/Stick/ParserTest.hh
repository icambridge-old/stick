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

  public function testPutsLoopContextInLoopNode(): void {

      $tokens = new TokenCollection();
      $tokens->add(new Token(Token::TYPE_BLOCK_START, ""));
      $tokens->add(new Token(Token::TYPE_NAME, "for"));
      $tokens->add(new Token(Token::TYPE_NAME, "var"));
      $tokens->add(new Token(Token::TYPE_OPERATOR, "in"));
      $tokens->add(new Token(Token::TYPE_NAME, "array"));
      $tokens->add(new Token(Token::TYPE_BLOCK_END, ""));
      $tokens->add(new Token(Token::TYPE_TEXT, "Hello"));
      $tokens->add(new Token(Token::TYPE_BLOCK_START, ""));
      $tokens->add(new Token(Token::TYPE_NAME, "endfor"));
      $tokens->add(new Token(Token::TYPE_BLOCK_END, ""));
      $tokens->add(new Token(Token::TYPE_EOF, ""));

      $parser = new Parser();
      $nodes = $parser->parse($tokens)->getChildren();
      $this->expect(is_a($nodes[0], '\\Stick\\Node\\ForLoop'))->toEqual(true);
      $blockNodes = $nodes[0]->getChildren();
      $this->expect(is_a($blockNodes[0], '\\Stick\\Node\\Text'))->toEqual(true);
  }

  public function testThrowsExceptionWhenEndIfInLoop(): void {

      $tokens = new TokenCollection();
      $tokens->add(new Token(Token::TYPE_BLOCK_START, ""));
      $tokens->add(new Token(Token::TYPE_NAME, "for"));
      $tokens->add(new Token(Token::TYPE_NAME, "var"));
      $tokens->add(new Token(Token::TYPE_OPERATOR, "in"));
      $tokens->add(new Token(Token::TYPE_NAME, "array"));
      $tokens->add(new Token(Token::TYPE_BLOCK_END, ""));
      $tokens->add(new Token(Token::TYPE_TEXT, "Hello"));
      $tokens->add(new Token(Token::TYPE_BLOCK_START, ""));
      $tokens->add(new Token(Token::TYPE_NAME, "endif"));
      $tokens->add(new Token(Token::TYPE_BLOCK_END, ""));
      $tokens->add(new Token(Token::TYPE_EOF, ""));

      $parser = new Parser();
      $this->expectCallable(
            () ==> {$parser->parse($tokens)->getChildren();}
        )->toThrow("Stick\\Exception\\InvalidSyntax");

  }

}
