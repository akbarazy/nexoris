#pragma once
#include <raylib.h>
#include <raymath.h>

namespace nexoris {
namespace engine {
namespace ecs {

// Represents a 2D Transform
struct Transform2D {
    Vector2 position = {0.0f, 0.0f};
    Vector2 velocity = {0.0f, 0.0f};
    Vector2 previousPosition = {0.0f, 0.0f}; // Used for sliding collision resolution
};

// Represents a graphical representation
struct Renderable {
    Color color = WHITE;
    Vector2 size = {32.0f, 32.0f};
};

// Represents an axis-aligned bounding box for collisions
struct BoxCollider {
    Vector2 size = {32.0f, 32.0f};
    Vector2 offset = {0.0f, 0.0f};
};

// Tag component for the player input receiver
struct PlayerInput {
    float speed = 5.0f;
};

// Tag component for the camera to follow
struct CameraTarget {
};

// Tag component for static map objects
struct StaticBody {
};

} // namespace ecs
} // namespace engine
} // namespace nexoris
