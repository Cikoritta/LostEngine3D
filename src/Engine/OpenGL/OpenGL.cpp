#include "OpenGL.hpp"

#include "../Debug/Debug.hpp"


bool le::OpenGl::m_gladInitialized = false;

bool le::OpenGl::m_glfwInitialized = false;


void le::OpenGl::glfwErrorCallback(int error, const char* description)
{
	LOG_ERROR("GLFW Error: " + std::format("{} ", error) + std::string(description));
}


void le::OpenGl::InitGLFW()
{
	if (!m_glfwInitialized)
	{
		glfwSetErrorCallback(glfwErrorCallback);

		if (!glfwInit())
			LOG_ERROR("Failed to initialize GLFW.");
		else
			LOG_INFO("GLFW initialized successfully.");

		m_glfwInitialized = true;
	}
	else
	{
		LOG_WARN("GLFW Reinitialization.");
	}
}

void le::OpenGl::InitGLAD()
{
	if (!m_gladInitialized)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			LOG_ERROR("Failed to initialize GLAD.");
		else
			LOG_INFO("GLAD initialized successfully.");

		m_gladInitialized = true;
	}
	else
	{
		LOG_WARN("GLAD Reinitialization.");
	}
}
