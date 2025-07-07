#include "Window.hpp"

#include "../Debug/Debug.hpp"
#include "../IniParser/IniParser.hpp"


void le::Window::resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


le::Window::Window(const Mode mode, const glm::uvec2& size, const std::string_view& title)
{
	create(mode, size, title);
}


le::Window::~Window()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);

		m_window = nullptr;
	}
}


void le::Window::create(const Mode mode, const glm::uvec2& size, const std::string_view& title)
{
	m_monitor = glfwGetPrimaryMonitor();

	if (!m_monitor)
		LOG_WARN("Failed to get primary monitor");

	m_videoMode = glfwGetVideoMode(m_monitor);

	if (!m_videoMode)
		LOG_WARN("Failed to get video mode of primary monitor");


	switch (mode)
	{
	case Mode::Window:

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_window = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);

		break;

	case Mode::Fullscreen:

		m_window = glfwCreateWindow(size.x, size.y, title.data(), m_monitor, nullptr);

		break;

	case Mode::Borderless:

		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

		m_window = glfwCreateWindow(m_videoMode->width, m_videoMode->height, title.data(), nullptr, nullptr);

		glfwSetWindowPos(m_window, 0, 0);

		break;

	default:
		LOG_ERROR("Unknown window mode specified");
		return;
	}
	


	if (!m_window)
	{
		glfwTerminate();

		LOG_ERROR("Failed to create GLFW window");
	}


	glfwMakeContextCurrent(m_window);

	OpenGl::InitGLAD();


	if (INI_GET(bool, GLOBAL_CONFIG_PATH.data(), "Display.vsync"))
		glfwSwapInterval(1);


	glfwSetWindowSizeCallback(m_window, resizeCallback);


	glm::uvec2 windowSize = getSize();

	glViewport(0, 0, windowSize.x, windowSize.y);
}


bool le::Window::isOpen() const
{
	return !glfwWindowShouldClose(m_window);
}


void le::Window::pollEvents() const
{
	glfwPollEvents();
}


glm::uvec2 le::Window::getSize() const
{
	int width = 0, height = 0;

	glfwGetWindowSize(m_window, &width, &height);

	return { width, height };
}

glm::uvec2 le::Window::getMonitorSize() const
{
	return { m_videoMode->width, m_videoMode->height };
}


void le::Window::setTitle(const std::string_view& title) const
{
	glfwSetWindowTitle(m_window, title.data());
}

std::string le::Window::getTitle() const
{
	return glfwGetWindowTitle(m_window);
}


void le::Window::setVSyncEnabled(bool enabled) const
{
	if (enabled)
	{
		glfwSwapInterval(1);
		LOG_INFO("VSync enabled");
	}
	else
	{
		glfwSwapInterval(0);
		LOG_INFO("VSync disabled");
	}
}


glm::ivec2 le::Window::getPosition() const
{
	int x = 0, y = 0;

	glfwGetWindowPos(m_window, &x, &y);

	return { static_cast<float>(x), static_cast<float>(y) };
}

void le::Window::setPosition(const glm::ivec2& position) const
{
	glfwSetWindowPos(m_window, position.x, position.y);

	LOG_INFO("Window position set to: " + std::to_string(position.x) + ", " + std::to_string(position.y));
}


glm::vec2 le::Window::getAspectRatio() const
{
	glm::uvec2 windowSize = getSize();

	glm::uvec2 monitorSize = getMonitorSize();


	return { static_cast<float>(windowSize.x) / static_cast<float>(monitorSize.x),
			static_cast<float>(windowSize.y) / static_cast<float>(monitorSize.y) };
}


void le::Window::clear() const
{
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void le::Window::draw() const
{
	glfwSwapBuffers(m_window);
}
