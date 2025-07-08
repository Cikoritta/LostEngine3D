#include "TestScene.hpp"

#include "../../Engine/Debug/Debug.hpp"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "../../Engine/Input/Input.hpp"

#pragma region TestScene

void TestScene::Awake()
{
	
}

void TestScene::Start()
{
    shader.loadFromFile("shader/sprite.vert", "shader/sprite.frag");

    le::Vertex vertices[] = {
        // Front face
        {{-0.5, -0.5,  0.5}, {0.0, 0.0}, {0, 0, 1}, {1,0,0,1}},
        {{ 0.5, -0.5,  0.5}, {1.0, 0.0}, {0, 0, 1}, {0,1,0,1}},
        {{ 0.5,  0.5,  0.5}, {1.0, 1.0}, {0, 0, 1}, {0,0,1,1}},
        {{-0.5,  0.5,  0.5}, {0.0, 1.0}, {0, 0, 1}, {1,1,1,1}},

        // Back face
        {{ 0.5, -0.5, -0.5}, {0.0, 0.0}, {0, 0, -1}, {1,0,0,1}},
        {{-0.5, -0.5, -0.5}, {1.0, 0.0}, {0, 0, -1}, {0,1,0,1}},
        {{-0.5,  0.5, -0.5}, {1.0, 1.0}, {0, 0, -1}, {0,0,1,1}},
        {{ 0.5,  0.5, -0.5}, {0.0, 1.0}, {0, 0, -1}, {1,1,1,1}},

        // Left face
        {{-0.5, -0.5, -0.5}, {0.0, 0.0}, {-1, 0, 0}, {1,0,0,1}},
        {{-0.5, -0.5,  0.5}, {1.0, 0.0}, {-1, 0, 0}, {0,1,0,1}},
        {{-0.5,  0.5,  0.5}, {1.0, 1.0}, {-1, 0, 0}, {0,0,1,1}},
        {{-0.5,  0.5, -0.5}, {0.0, 1.0}, {-1, 0, 0}, {1,1,1,1}},

        // Right face
        {{ 0.5, -0.5,  0.5}, {0.0, 0.0}, {1, 0, 0}, {1,0,0,1}},
        {{ 0.5, -0.5, -0.5}, {1.0, 0.0}, {1, 0, 0}, {0,1,0,1}},
        {{ 0.5,  0.5, -0.5}, {1.0, 1.0}, {1, 0, 0}, {0,0,1,1}},
        {{ 0.5,  0.5,  0.5}, {0.0, 1.0}, {1, 0, 0}, {1,1,1,1}},

        // Top face
        {{-0.5,  0.5,  0.5}, {0.0, 0.0}, {0, 1, 0}, {1,0,0,1}},
        {{ 0.5,  0.5,  0.5}, {1.0, 0.0}, {0, 1, 0}, {0,1,0,1}},
        {{ 0.5,  0.5, -0.5}, {1.0, 1.0}, {0, 1, 0}, {0,0,1,1}},
        {{-0.5,  0.5, -0.5}, {0.0, 1.0}, {0, 1, 0}, {1,1,1,1}},

        // Bottom face
        {{-0.5, -0.5, -0.5}, {0.0, 0.0}, {0, -1, 0}, {1,0,0,1}},
        {{ 0.5, -0.5, -0.5}, {1.0, 0.0}, {0, -1, 0}, {0,1,0,1}},
        {{ 0.5, -0.5,  0.5}, {1.0, 1.0}, {0, -1, 0}, {0,0,1,1}},
        {{-0.5, -0.5,  0.5}, {0.0, 1.0}, {0, -1, 0}, {1,1,1,1}},
    };

    // Индексы треугольников
    std::vector<uint> indices = {
        // Front
        0,1,2, 2,3,0,
        // Back
        4,5,6, 6,7,4,
        // Left
        8,9,10, 10,11,8,
        // Right
        12,13,14, 14,15,12,
        // Top
        16,17,18, 18,19,16,
        // Bottom
        20,21,22, 22,23,20
    };

    mesh.Init(
        std::vector<le::Vertex>(std::begin(vertices), std::end(vertices)),
        indices,
        std::move(shader)
	);

    texture.loadFromFile("texture.png");

    shader.setUniform1i("uTexture", 0);

    camera = le::Camera(m_window.getAspectRatio());
}

void TestScene::Update(float deltaTime)
{
}

void TestScene::FixedUpdate(float fixedDeltaTime)
{
    const float cameraSpeed = 2.5f * fixedDeltaTime;
    const float rotationSpeed = 50.0f * fixedDeltaTime;

    glm::vec3 position = camera.getPosition();
    glm::vec3 target = camera.getTarget();
    glm::vec3 up = camera.getUp();

    glm::vec3 forward = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(forward, up));

    // Движение WASD
    if (KEY_PRESSED(GLFW_KEY_W))
        position += forward * cameraSpeed;
    if (KEY_PRESSED(GLFW_KEY_S))
        position -= forward * cameraSpeed;
    if (KEY_PRESSED(GLFW_KEY_A))
        position -= right * cameraSpeed;
    if (KEY_PRESSED(GLFW_KEY_D))
        position += right * cameraSpeed;

    // Поворот камеры стрелками
    if (KEY_PRESSED(GLFW_KEY_LEFT))
        camera.yaw -= rotationSpeed;
    if (KEY_PRESSED(GLFW_KEY_RIGHT))
        camera.yaw += rotationSpeed;
    if (KEY_PRESSED(GLFW_KEY_UP))
        camera.pitch += rotationSpeed;
    if (KEY_PRESSED(GLFW_KEY_DOWN))
        camera.pitch -= rotationSpeed;

    // Ограничиваем pitch, чтобы камера не перевернулась
    if (camera.pitch > 89.0f)
        camera.pitch = 89.0f;
    if (camera.pitch < -89.0f)
        camera.pitch = -89.0f;

    // Пересчитываем forward по yaw/pitch
    glm::vec3 newForward;
    newForward.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    newForward.y = sin(glm::radians(camera.pitch));
    newForward.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));

    forward = glm::normalize(newForward);
    camera.setTarget(position + forward);

    // Обновляем позицию
    camera.setPosition(position);
}

void TestScene::Draw()
{
    texture.bind(0);
    shader.setUniform1i("uUseTexture", 1);
    shader.setUniformMat4("uModel", glm::mat4(1.0f));
    camera.setShaderUniforms(shader);
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