#pragma once
#include "../Common.hpp"
#include "../Shader/Shader.hpp"


namespace le
{
	struct Vertex
	{
		glm::vec3 position;

		glm::vec2 texCoords;

		glm::vec3 normal;

		glm::vec4 color;
	};

	class Mesh
	{
		uint m_vao = 0U;

		uint m_vbo = 0U;

		uint m_ebo = 0U;


		Shader m_shader;


		uint m_vertexCount = 0U;

		uint m_indexCount = 0U;

	public:

		Mesh() = default;

		~Mesh();


		void Init(const std::vector<Vertex>& vertices, const std::vector<uint>& indices, Shader&& shader);

		void Draw() const;
	};
}