#pragma once
#include <raylib.h>
#include <unordered_map>

namespace nexoris {
namespace engine {

enum class Action {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    Interact,
    Attack,
    Count // Used for sizing arrays if needed
};

class InputManager {
public:
    InputManager();
    ~InputManager() = default;

    void Update();

    // Check if an action button is currently held down
    bool IsActionDown(Action action) const;
    // Check if an action button was pressed this frame
    bool IsActionPressed(Action action) const;
    // Check if an action button was released this frame
    bool IsActionReleased(Action action) const;

    // Map a keyboard key to an action
    void BindKey(Action action, KeyboardKey key);
    
private:
    std::unordered_map<Action, KeyboardKey> m_KeyBindings;
};

} // namespace engine
} // namespace nexoris
