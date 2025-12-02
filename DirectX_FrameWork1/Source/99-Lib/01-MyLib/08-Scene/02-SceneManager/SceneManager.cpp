#include "SceneManager.h"

#include "../../07-Component/03-Collider/99-ColliderManager/01-Collider2DManager/Collider2DManager.h"
#include "../../02-Renderer/98-RendererManager/RendererManager.h"
#include "../01-Scenes/TitleScene.h"



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

#include "../../01-System/System.h"
void SceneManager::UnloadScene()
{
	System::GetInstance().ClearManagersData();
	curScene->UnInit();
}
