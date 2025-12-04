#pragma once
#include "../01-Scenes/00-BaseScene/BaseScene.h"

class SceneManager
{
private:
	std::unique_ptr<BaseScene> curScene;	//現在のシーン
	std::unique_ptr<BaseScene> nextScene;	//次のシーン

	SceneManager() = default;
	~SceneManager() = default;

public:
	static SceneManager& GetInstance()
	{
		static SceneManager instance;
		return instance;
	}

	void Init();
	void UnInit();

	/**
	* @brief	シーンをロード
	* @param	std::unique_ptr<BaseScene>	_up_scene	ユニークポインタのシーン
	*/
	void LoadScene(std::unique_ptr<BaseScene> _uq_scene);
	void ChangeScene();	// シーン変更

	void SetUpScene();	// シーンのセットアップ
	void UnloadScene();	// シーンの後片付け

};

