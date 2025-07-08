#pragma once
#include "../Common.hpp"

namespace le
{
	class Texture2D
	{
		uint m_textureID = 0U;

		int m_width;
		int m_height;
		int m_channels;

	public:

		Texture2D() = default;

		~Texture2D() = default;


		void loadFromFile(const std::string& filePath);


		void bind(GLuint unit) const;
	};
}