#pragma once

#include "../Common.hpp"
#include "../Shader/Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace le
{
	class Camera
	{
        glm::vec3 position;

        glm::vec3 target;

        glm::vec3 up;


        float fov;

        float aspectRatio;

        float nearClip;

        float farClip;

	public:
        float yaw = -90.0f;

        float pitch = 0.0f;
        Camera(float aspectRatio = 16.0f / 9.0f,
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
               glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               float fov = 90.0f,
               float nearClip = 0.1f,
			float farClip = 100.0f);

		~Camera() = default;


        glm::mat4 GetViewMatrix() const;

        glm::mat4 GetProjectionMatrix() const;


        void setShaderUniforms(Shader& shader) const;


        void setPosition(const glm::vec3& newPosition);

        glm::vec3 getPosition() const;


        void setTarget(const glm::vec3& newTarget);

        glm::vec3 getTarget() const;


        void setUp(const glm::vec3& newUp);

        glm::vec3 getUp() const;
	};
}