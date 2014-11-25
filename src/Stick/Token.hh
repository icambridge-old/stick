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

    public function isName(): bool {
        return $this->type == self::TYPE_NAME;
    }

    public function isOperator(): bool {
        return $this->type == self::TYPE_OPERATOR;
    }

    public function isStartBlock(): bool {
        return $this->type == self::TYPE_BLOCK_START;
    }

    public function isEndBlock(): bool {
        return $this->type == self::TYPE_BLOCK_END;
    }

    public function isVariableEnd() : bool
    {
        return $this->type == self::TYPE_VARIABLE_END;
    }
}
