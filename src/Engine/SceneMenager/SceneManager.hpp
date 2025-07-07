#pragma once
#include "../Events/Events.hpp"
#include "../Window/Window.hpp"
#include "../Scene/Scene.hpp"
#include "../Clock/Clock.hpp"

#include "../Common.hpp"


namespace le
{
	class SceneManager
	{
		using SceneFactory = std::function<std::shared_ptr<Scene>()>;

		using SceneMap = std::unordered_map<std::string, SceneFactory>;


		std::shared_ptr<Scene>	m_currentScene;

		SceneMap				m_sceneFactory;


		Clock					m_clock;

		float					m_deltaTime = 0.0f;

		float 					m_accumulatedTime = 0.0f;

		float                   m_lastTime = 0.0f;

		float                   m_currentTime = 0.0f;

	public:

		SceneManager();


		void addScene(const std::string& name, SceneFactory factory);

		void sceneChange(const le::Events::ChangeScene& event);


		void gameLoop(Window& window);
	};
}