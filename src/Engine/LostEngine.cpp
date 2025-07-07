#include "LostEngine.hpp"

#include "Debug/Debug.hpp"
#include "Events/Events.hpp"
#include "IniParser/IniParser.hpp"

#include "../Game/Scenes/TestScene.hpp"


le::LostEngine::LostEngine()
{
	le::OpenGl::InitGLFW();
}


void le::LostEngine::InitEngine()
{
	LOG_INFO("Engine initialization...");


	m_window.create(static_cast<le::Window::Mode>(INI_GET(int, GLOBAL_CONFIG_PATH.data(), "Display.mode")), INI_GET(glm::ivec2, GLOBAL_CONFIG_PATH.data(), "Display.windowSize"));


	m_sceneManager.addScene("TestScene", [&]() -> std::shared_ptr<le::Scene>
	{
		return std::make_shared<TestScene>(m_window, "TestScene");
	});


	le::EventBus::Get().Emit(le::Events::ChangeScene("TestScene"));


	LOG_INFO("Engine initialization complate.");
}

void le::LostEngine::RunEngine()
{
	InitEngine();

	while (m_window.isOpen())
	{
		m_sceneManager.gameLoop(m_window);
	}
}