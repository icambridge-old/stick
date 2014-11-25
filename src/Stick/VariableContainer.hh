<?hh

namespace Stick;

class VariableContainer
{
    private Map<string, mixed> $variables = Map{};

    public function set(string $key, mixed $value): void
    {
        $this->variables[$key] = $value;
    }

    public function get(string $key): mixed
    {
        return $this->variables[$key];
    }
}
