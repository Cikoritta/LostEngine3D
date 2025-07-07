#include "SceneManager.hpp"

#include "../Debug/Debug.hpp"


le::SceneManager::SceneManager()
{
	EventBus::Get().Subscribe<le::Events::ChangeScene>
	(
		[this](const le::Events::ChangeScene& event)
		{
			sceneChange(event);
		}
	);
}


void le::SceneManager::addScene(const std::string& name, SceneFactory factory)
{
	m_sceneFactory[name] = std::move(factory);
}

void le::SceneManager::sceneChange(const le::Events::ChangeScene& event)
{
	LOG_DEBUG("Scene change event received: " + event.newSceneName);

	if (m_currentScene)
		m_currentScene->Destroy();


	if (m_sceneFactory.find(event.newSceneName) == m_sceneFactory.end())
		LOG_ERROR("Scene not found: " + event.newSceneName);


	m_currentScene = m_sceneFactory[event.newSceneName]();


	m_currentScene->Awake();

	m_currentScene->Start();


	m_clock.start();

	m_lastTime = m_clock.getTime();


	LOG_INFO("Scene changed to: " + event.newSceneName);
}

void le::SceneManager::gameLoop(Window& window)
{
	m_currentTime = m_clock.getTime();

	m_deltaTime = m_currentTime - m_lastTime;

	m_lastTime = m_currentTime;


	m_accumulatedTime += m_deltaTime;


	window.pollEvents();


	m_currentScene->Update(m_deltaTime);


	while (m_accumulatedTime >= FIXED_DELTA_TIME)
	{
		m_currentScene->FixedUpdate(FIXED_DELTA_TIME);

		m_accumulatedTime -= FIXED_DELTA_TIME;
	}


	window.clear();

	m_currentScene->Draw();

	window.draw();
}
