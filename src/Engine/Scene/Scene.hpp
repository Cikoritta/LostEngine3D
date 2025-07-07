#pragma once
#include <entt/entt.hpp>
#include <string>

#include "../Window/Window.hpp"


namespace le
{
	class Scene
	{
	protected:

		entt::registry	m_registry;

		std::string		m_name;


		Window&			m_window;

	public:

		Scene(Window& window, const std::string& name): m_window(window), m_name(name) {}

		virtual ~Scene() = default;


		virtual void Awake() = 0;

		virtual void Start() = 0;

		virtual void Update(float deltaTime) = 0;

		virtual void FixedUpdate(float fixedDeltaTime) = 0;

		virtual void Draw() = 0;

		virtual void Destroy() = 0;
	};
}