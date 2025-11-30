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
	static RendererManager& rendererMng = RendererManager::GetInstance();
	rendererMng.ClearScreen();
	curScene->Draw();
	rendererMng.SwapChain();
}



void SceneManager::Init()
{
	curScene = std::make_unique<TitleScene>();
	SetUpScene();
}

void SceneManager::UnInit()
{
}

void SceneManager::ChangeScene()
{
	if (nextScene != nullptr)
	{
		UnloadScene();
		curScene = std::move(nextScene);
		Collider2DManager::GetInstance().UnInit();
		SetUpScene();
	}
}

void SceneManager::LoadScene(std::unique_ptr<BaseScene> _uq_scene)
{
	if (_uq_scene != nullptr)
		nextScene = std::move(_uq_scene);
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

#include "../../01-System/System.h"
void SceneManager::UnloadScene()
{
	System::GetInstance().ClearManagersData();
	curScene->UnInit();
}
