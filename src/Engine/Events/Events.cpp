#include "Events.hpp"

void le::EventBus::Emit(const Event& event)
{
    auto it = subscribers.find(typeid(event));

    if (it != subscribers.end()) 
    {
        for (auto& callback : it->second) 
        {
            callback(event);
        }
    }
}


le::EventBus& le::EventBus::Get()
{
    static EventBus instance;

    return instance;
}
