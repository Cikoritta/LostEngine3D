#include "TestScene.hpp"

#include "../../Engine/Debug/Debug.hpp"

#pragma region TestScene

void TestScene::Awake()
{
	
}

void TestScene::Start()
{
    shader.loadFromFile("shader/sprite.vert", "shader/sprite.frag");

     le::Vertex vertices[] = {
        // position           texCoords   normal            color
        {{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f}, {0, 0, 1}, {1, 0, 0, 1}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}, {0, 0, 1}, {0, 1, 0, 1}},
        {{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, {0, 0, 1}, {0, 0, 1, 1}}, 

        {{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f}, {0, 0, 1}, {1, 0, 0, 1}},
        {{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, {0, 0, 1}, {0, 0, 1, 1}},
        {{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f}, {0, 0, 1}, {1, 1, 1, 1}},
    };

    mesh.Init(
        std::vector<le::Vertex>(std::begin(vertices), std::end(vertices)),
        std::vector<uint>{0, 1, 2, 3, 4, 5},
        std::move(shader)
	);

    texture.loadFromFile("texture.png");

    shader.setUniform1i("uTexture", 0);
}

void TestScene::Update(float deltaTime)
{
}

void TestScene::FixedUpdate(float fixedDeltaTime)
{
}

void TestScene::Draw()
{
    texture.bind(0);
    shader.use();
	mesh.Draw();
}

void TestScene::Destroy()
{
	
}

#pragma endregion

#pragma region TestScene2

void TestScene2::Awake()
{
	LOG_DEBUG("TestScene2 Awake called");
}

void TestScene2::Start()
{
	LOG_DEBUG("TestScene2 Start called");
}

void TestScene2::Update(float deltaTime)
{
}

void TestScene2::FixedUpdate(float fixedDeltaTime)
{
}

void TestScene2::Draw()
{
}

void TestScene2::Destroy()
{
	LOG_DEBUG("TestScene2 Destroy called");
}

#pragma endregion