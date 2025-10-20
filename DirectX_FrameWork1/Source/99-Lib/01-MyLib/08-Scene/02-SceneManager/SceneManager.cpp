#include "SceneManager.h"

#include "../../07-Component/03-Collider/99-ColliderManager/01-Collider2DManager/Collider2DManager.h"
#include "../../02-Renderer/98-RendererManager/RendererManager.h"
#include "../01-Scenes/TitleScene.h"


void SceneManager::Input()
{
	curScene->Input();
}

void SceneManager::Update()
{
	ChangeScene();
	curScene->Update();
	Collider2DManager::GetInstance().Update();
}

void SceneManager::Draw()
{
	static RendererManager& system = RendererManager::GetInstance();
	system.ClearScreen();
	curScene->Draw();
	system.SwapChain();
}



void SceneManager::Init()
{
	RendererManager::GetInstance();
	curScene = std::make_unique<TitleScene>();
	SetUpScene();
}

void SceneManager::UnInit()
{
}

void SceneManager::ChangeScene()
{
	auto scene = curScene->GetNextScene();
	if (scene != nullptr)
	{
		UnloadScene();
		curScene = std::move(scene);
		Collider2DManager::GetInstance().UnInit();
		SetUpScene();
	}
}

void SceneManager::SetUpScene()
{
	curScene->Init();
}

void SceneManager::RunScene()
{
	Input();
	Update();
	Draw();
}

void SceneManager::UnloadScene()
{
	curScene->UnInit();
}
