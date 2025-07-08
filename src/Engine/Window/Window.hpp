#pragma once
#include "../Common.hpp"


namespace le
{
	class Window
	{
	public:

		enum class Mode
		{
			Window,
			Fullscreen,
			Borderless
		};

	private:

		GLFWwindow*			m_window = nullptr;

		GLFWmonitor*		m_monitor = nullptr;

		const GLFWvidmode*	m_videoMode = nullptr;


		static void resizeCallback(GLFWwindow* window, int width, int height);

	public:

		Window() = default;

		Window(const Mode mode, const glm::uvec2& size = DEFAULT_WINDOW_SIZE, const std::string_view& title = GAME_NAME);

		~Window();


		GLFWwindow* getGLFWWindow() const;


		void create(const Mode mode, const glm::uvec2& size = DEFAULT_WINDOW_SIZE, const std::string_view& title = GAME_NAME);

		bool isOpen() const;


		void pollEvents() const;


		glm::uvec2 getSize() const;

		glm::uvec2 getMonitorSize() const;


		void setTitle(const std::string_view& title) const;

		std::string getTitle() const;


		void setVSyncEnabled(bool enabled) const;


		glm::ivec2 getPosition() const;

		void setPosition(const glm::ivec2& position) const;


		float getAspectRatio() const;


		void clear() const;

		void draw() const;
	};
}