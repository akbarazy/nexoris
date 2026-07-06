#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <memory>

namespace nexoris {
namespace engine {

enum class EventType {
    WindowResize,
    PlayerDied,
    OpenUI_Blacksmith,
    // Add more as needed
};

// Base class for event data
struct EventData {
    virtual ~EventData() = default;
};

// Specific event data example
struct WindowResizeEventData : public EventData {
    int newWidth;
    int newHeight;
};

using EventCallback = std::function<void(std::shared_ptr<EventData>)>;

class EventManager {
public:
    EventManager() = default;
    ~EventManager() = default;

    // Subscribe to an event
    void Subscribe(EventType type, EventCallback callback);

    // Publish an event
    void Publish(EventType type, std::shared_ptr<EventData> data = nullptr);

    // Clear all subscriptions
    void Clear();

private:
    std::unordered_map<EventType, std::vector<EventCallback>> m_Subscribers;
};

} // namespace engine
} // namespace nexoris
