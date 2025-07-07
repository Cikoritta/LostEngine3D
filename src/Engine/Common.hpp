#pragma once
#include <string>
#include <string_view>
#include <glm/glm.hpp>
#include <unordered_map>

#include "OpenGL/OpenGL.hpp"

namespace le
{
	constexpr std::string_view	GAME_NAME = "Pokemon Age of Dragons";

	constexpr glm::uvec2		DEFAULT_WINDOW_SIZE = { 1280U, 720U };

	constexpr bool				DEBUG_MODE = true;


	constexpr float				FIXED_DELTA_TIME = 1.0f / 60.0f; // 60 FPS

	constexpr std::string_view	GLOBAL_CONFIG_PATH = "config.ini";
}