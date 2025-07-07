#pragma once
#include "Common.hpp"
#include "Window/Window.hpp"
#include "SceneMenager/SceneManager.hpp"


namespace le
{
	class LostEngine
	{
		Window m_window;

		SceneManager m_sceneManager;


		void InitEngine();

	public:

		LostEngine();

		void RunEngine();
	};
}