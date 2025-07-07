#include "TestScene.hpp"

#include "../../Engine/Debug/Debug.hpp"


#pragma region TestScene

void TestScene::Awake()
{
	LOG_DEBUG("TestScene Awake called");
}

void TestScene::Start()
{
	LOG_DEBUG("TestScene Start called");
}

void TestScene::Update(float deltaTime)
{
}

void TestScene::FixedUpdate(float fixedDeltaTime)
{
}

void TestScene::Draw()
{
}

void TestScene::Destroy()
{
	LOG_DEBUG("TestScene Destroy called");
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