#include "SceneManager.h"

#include "Collider2DManager.h"
#include "system.h"
#include "Sprite2DRenderer.h"
#include "TitleScene.h"
#include "controller.h"


void SceneManager::Init()
{
	System::GetInstance();
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
#if !defined(WIN64)
	SetControllerRightAngleBase();
	SetControllerLeftAngleBase();
#endif
	curScene->Init();
}

void SceneManager::UnloadScene()
{
	curScene->UnInit();
}

void SceneManager::Input()
{
	curScene->Input();
}

void SceneManager::Update()
{
	curScene->Update();
	Collider2DManager::GetInstance().Update();
}

void SceneManager::Draw()
{
	System* system = &System::GetInstance();
	system->ScreenClear();
	curScene->Draw();
	system->SwapBuffers();

	system->PollEvents();	//‰¼’u‚«
}
