#pragma once
#include <functional>
#include <unordered_map>
#include <memory>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <string>

namespace le
{
	struct Event
	{
		virtual ~Event() = default;
	};


	using EventCallback = std::function<void(const Event&)>;


	class EventBus
	{
		std::unordered_map<std::type_index, std::vector<EventCallback>> subscribers;

	public:

		template<typename T>
		void Subscribe(std::function<void(const T&)> callback);

		void Emit(const Event& event);


		static EventBus& Get();
	};

	template<typename T>
	inline void EventBus::Subscribe(std::function<void(const T&)> callback)
	{
		EventCallback wrapper = [callback](const Event& e)
		{
			callback(static_cast<const T&>(e));
		};

		subscribers[typeid(T)].push_back(wrapper);
	}


	namespace Events
	{
		struct ChangeScene : public Event
		{
			std::string newSceneName;

			ChangeScene(const std::string& name) : newSceneName(name) {}
		};
	}
}