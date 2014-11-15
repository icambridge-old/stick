<?hh

namespace Stick;

class Token
{
    const TYPE_EOF   = 'EOF';
    const TYPE_TEXT  = 'TEXT';
    const TYPE_BLOCK_START = 'BLOCK_START';
    const TYPE_BLOCK_END = 'BLOCK_END';
    const TYPE_VARIABLE_START = 'VARIABLE_START';
    const TYPE_VARIABLE_END = 'VARIABLE_END';
    const TYPE_OPERATOR = 'OPERATOR';
    const TYPE_NAME = "NAME";

    public function __construct(private string $type, private string $value) {}

    public function getType(): string {
        return $this->type;
    }

    public function getValue(): string {
        return $this->value;
    }
}
