#include "Camera.hpp"


le::Camera::Camera(float aspectRatio, glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float nearClip, float farClip) 
	: position(position), target(target), up(up), fov(fov), aspectRatio(aspectRatio), nearClip(nearClip), farClip(farClip)
{
}

glm::mat4 le::Camera::GetViewMatrix() const
{
	return glm::lookAt(position, target, up);
}


glm::mat4 le::Camera::GetProjectionMatrix() const
{
	return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}


void le::Camera::setShaderUniforms(le::Shader& shader) const
{
	shader.setUniformMat4("uView", GetViewMatrix());
	shader.setUniformMat4("uProjection", GetProjectionMatrix());
}


void le::Camera::setPosition(const glm::vec3& newPosition)
{
	position = newPosition;
}

glm::vec3 le::Camera::getPosition() const
{
	return position;
}


void le::Camera::setTarget(const glm::vec3& newTarget)
{
	target = newTarget;
}

glm::vec3 le::Camera::getTarget() const
{
	return target;
}


void le::Camera::setUp(const glm::vec3& newUp)
{
	up = newUp;
}

glm::vec3 le::Camera::getUp() const
{
	return up;
}
