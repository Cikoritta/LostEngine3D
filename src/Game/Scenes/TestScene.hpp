#pragma once
#include "../../Engine/Scene/Scene.hpp"
#include "../../Engine/Texture/Texture.hpp"
#include "../../Engine/Shader/Shader.hpp"
#include "../../Engine/Mesh/Mesh.hpp"


class TestScene : public le::Scene
{
	le::Texture2D texture;

	le::Shader shader;

	le::Mesh mesh;

public:

	TestScene(le::Window& window, const std::string& name) : le::Scene(window, name) {}


	void Awake() override;

	void Start() override;

	void Update(float deltaTime) override;

	void FixedUpdate(float fixedDeltaTime) override;

	void Draw() override;

	void Destroy() override;
};

class TestScene2 : public le::Scene
{


public:

	TestScene2(le::Window& window, const std::string& name) : le::Scene(window, name) {}


	void Awake() override;

	void Start() override;

	void Update(float deltaTime) override;

	void FixedUpdate(float fixedDeltaTime) override;

	void Draw() override;

	void Destroy() override;
};