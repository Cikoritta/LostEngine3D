#pragma once
#include "../Common.hpp"
#include "../Window/Window.hpp"

namespace le
{
	#define KEY_PRESS(key) le::Input::isKeyPress(key)
	#define KEY_PRESSED(key) le::Input::isKeyPressed(key)
 
	class Input
	{
		static Window* m_window;

		static std::unordered_map<int, bool> m_keyStates;

	public:

		static void init(Window& window);

		static bool isKeyPress(uint key);

		static bool isKeyPressed(uint key);
	};
}