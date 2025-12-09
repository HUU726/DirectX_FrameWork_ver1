#include "SceneManager.h"

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


/**
* @note		未初期化シーンをnextSceneにムーブ
*			※この後ChangeSceneへ
*/
void SceneManager::LoadScene(std::unique_ptr<BaseScene> _uq_scene)
{
	if (_uq_scene != nullptr)
		nextScene = std::move(_uq_scene);
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
	}
}

void SceneManager::SetUpScene()
{
	curScene->Init();
}



#include "../../01-System/System.h"
/**
* @note		Systemクラスで管理しているManager類を解放
*			Scene内のデータを解放
*/
void SceneManager::UnloadScene()
{
	System::GetInstance().ClearManagersData();
	curScene->UnInit();
}
