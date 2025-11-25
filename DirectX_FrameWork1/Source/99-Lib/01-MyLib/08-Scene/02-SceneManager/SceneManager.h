#pragma once
#include "../01-Scenes/00-BaseScene/BaseScene.h"


#include "../../06-GameObject/999-GameObjectManager/GameObjectManager.h"

class SceneManager
{
private:
	std::unique_ptr<BaseScene> curScene;

	GameObjectManager& gameObjMng = GameObjectManager::GetInstance();



	SceneManager() = default;
	~SceneManager() = default;

	void Input();
	void Update();
	void Draw();

public:
	static SceneManager& GetInstance()
	{
		static SceneManager instance;
		return instance;
	}

	void Init();
	void UnInit();

	void ChangeScene();	// シーン変更
	void SetUpScene();	// シーンのセットアップ
	void RunScene();
	void UnloadScene();	// シーンの後片付け

};

