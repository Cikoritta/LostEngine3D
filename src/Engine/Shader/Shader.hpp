#pragma once

#include "../Common.hpp"


namespace le
{
	class Shader
	{
		GLuint m_program = 0U;

		GLuint createShader(GLenum type, const std::string& source);


		void saveProgramBinary(const std::string& filePath) const;

		bool loadProgramBinary(const std::string& filePath);

	public:

		void loadFromSource(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

		void loadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		void use() const;


		void setUniform1i(const std::string& name, int value) const;

		void setUniform1f(const std::string& name, float value) const;

		void setUniformVec2(const std::string& name, const glm::vec2& vec) const;

		void setUniformVec3(const std::string& name, const glm::vec3& vec) const;

		void setUniformVec4(const std::string& name, const glm::vec4& vec) const;

		void setUniformMat4(const std::string& name, const glm::mat4& mat) const;
	};
}