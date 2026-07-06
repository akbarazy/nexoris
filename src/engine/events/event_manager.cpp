#include "engine/events/event_manager.hpp"

namespace nexoris {
namespace engine {

void EventManager::Subscribe(EventType type, EventCallback callback) {
    m_Subscribers[type].push_back(callback);
}

void EventManager::Publish(EventType type, std::shared_ptr<EventData> data) {
    auto it = m_Subscribers.find(type);
    if (it != m_Subscribers.end()) {
        for (auto& callback : it->second) {
            callback(data);
        }
    }
}

void EventManager::Clear() {
    m_Subscribers.clear();
}

} // namespace engine
} // namespace nexoris
