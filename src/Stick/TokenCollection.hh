<?hh //strict

namespace Stick;

class TokenCollection
{
    private int $counter = 0;
    private Vector<Token> $tokens = Vector{};


    public function add(Token $token): void
    {
        $this->tokens[] = $token;
    }

    public function next(): void
    {
        return $this->tokens[$this->counter++];
    }
}
