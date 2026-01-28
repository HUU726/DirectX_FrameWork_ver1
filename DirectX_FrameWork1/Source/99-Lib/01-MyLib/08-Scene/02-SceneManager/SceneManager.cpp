#include "SceneManager.h"

#include "../../02-Renderer/98-RendererManager/RendererManager.h"
#include "../../06-GameObject/999-GameObjectManager/GameObjectManager.h"

//#include "../../../../00-HEW2026/20-Scene/Test_HewScene2.h"
#include "../01-Scenes/TitleScene.h"
#include "../../../../00-HEW2026/20-Scene/02_StageSelectScene.h"

#include "../../03-Sound/Fsound.h"



void SceneManager::Init()
{
	curScene = std::make_unique<Hew_StageSelectScene>();
	SetUpScene();
}

void SceneManager::UnInit()
{
	UnloadScene();
}

/**
* @note		curSceneをnextSceneに変更＆初期化
*			※他インスタンスの更新処理が入る前にここを呼び出す
*/
void SceneManager::ChangeScene()
{
	if (nextScene != nullptr)
	{
		UnloadScene();
		curScene = std::move(nextScene);
		SetUpScene();
		nextFlg = false;
	}
	else
	{
		GameObjectManager::GetInstance().AddWaitToNow();
	}

	GameObjectManager::GetInstance().ClearDestroyQueue();
}

void SceneManager::SetUpScene()
{
	nextFlg  = false;
	curScene->Init();
	GameObjectManager::GetInstance().SetUpObject();
	SoundManager::GetInstance().SetUpSounds();
}



#include "../../01-System/System.h"
/**
* @note		Systemクラスで管理しているManager類を解放
*			Scene内のデータを解放
*/
void SceneManager::UnloadScene()
{
	SoundManager::GetInstance().ReleaseSounds();
	System::GetInstance().ClearManagersData();
	curScene->UnInit();
}
