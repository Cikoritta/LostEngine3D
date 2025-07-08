#include "Input.hpp"


le::Window* le::Input::m_window = nullptr;

std::unordered_map<int, bool> le::Input::m_keyStates;


void le::Input::init(Window& window)
{
	m_window = &window;
}

bool le::Input::isKeyPress(uint key)
{
    int state = glfwGetKey(m_window->getGLFWWindow(), key);

    if (state == GLFW_PRESS)
    {
        if (m_keyStates[key])
            return false;
        else
        {
            m_keyStates[key] = true;

            return true;
        }
    }
    else
    {
        m_keyStates[key] = false;

        return false;
    }
}

bool le::Input::isKeyPressed(uint key)
{
    return glfwGetKey(m_window->getGLFWWindow(), key) == GLFW_PRESS;
}
