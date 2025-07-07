#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>


namespace le
{
	class OpenGl
	{
		static bool m_gladInitialized;

		static bool m_glfwInitialized;


		static void glfwErrorCallback(int error, const char* description);

	public:

		static void InitGLFW();

		static void InitGLAD();
	};
}