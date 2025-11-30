#pragma once
#include "../01-Scenes/00-BaseScene/BaseScene.h"

class SceneManager
{
private:
	std::unique_ptr<BaseScene> curScene;
	std::unique_ptr<BaseScene> nextScene;

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
	void LoadScene(std::unique_ptr<BaseScene> _uq_scene);
	void SetUpScene();	// シーンのセットアップ
	void RunScene();
	void UnloadScene();	// シーンの後片付け

};

