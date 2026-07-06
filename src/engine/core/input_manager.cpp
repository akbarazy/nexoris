#include "engine/core/input_manager.hpp"

namespace nexoris {
namespace engine {

InputManager::InputManager() {
    // Default bindings
    BindKey(Action::MoveUp, KEY_W);
    BindKey(Action::MoveDown, KEY_S);
    BindKey(Action::MoveLeft, KEY_A);
    BindKey(Action::MoveRight, KEY_D);
    BindKey(Action::Interact, KEY_E);
    BindKey(Action::Attack, KEY_SPACE);
}

void InputManager::Update() {
    // Currently Raylib handles state internally per frame, so we might not need to manually buffer here.
    // In a more complex engine, we would store current frame state and previous frame state.
}

bool InputManager::IsActionDown(Action action) const {
    auto it = m_KeyBindings.find(action);
    if (it != m_KeyBindings.end()) {
        return IsKeyDown(it->second);
    }
    return false;
}

bool InputManager::IsActionPressed(Action action) const {
    auto it = m_KeyBindings.find(action);
    if (it != m_KeyBindings.end()) {
        return IsKeyPressed(it->second);
    }
    return false;
}

bool InputManager::IsActionReleased(Action action) const {
    auto it = m_KeyBindings.find(action);
    if (it != m_KeyBindings.end()) {
        return IsKeyReleased(it->second);
    }
    return false;
}

void InputManager::BindKey(Action action, KeyboardKey key) {
    m_KeyBindings[action] = key;
}

} // namespace engine
} // namespace nexoris
