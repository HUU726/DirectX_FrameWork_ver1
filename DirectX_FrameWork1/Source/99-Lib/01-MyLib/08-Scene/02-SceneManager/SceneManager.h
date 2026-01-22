#pragma once
#include "../01-Scenes/00-BaseScene/BaseScene.h"

class SceneManager
{
private:
	std::unique_ptr<BaseScene> curScene;	//現在のシーン
	std::unique_ptr<BaseScene> nextScene;	//次のシーン
	bool nextFlg;

	SceneManager() = default;
	~SceneManager() = default;

public:
	static SceneManager& GetInstance()
	{
		static SceneManager instance;
		return instance;
	}

	bool GetNext() { return nextFlg; }

	void Init();
	void UnInit();
	
	template<typename T>
	void LoadScene();

	void ChangeScene();	// シーン変更

	void SetUpScene();	// シーンのセットアップ
	void UnloadScene();	// シーンの後片付け

};


#include "../../06-GameObject/999-GameObjectManager/GameObjectManager.h"
#include "../../07-Component/03-Collider/99-ColliderManager/00-ColliderManager/ColliderManager.h"
#include "../../07-Component/03-Collider/01-Collider2D/00-Collider2D/Collider2D.h"
#include "../../07-Component/03-Collider/02-Collider3D/00-Collider3D/Collider3D.h"
template<typename T>
inline void SceneManager::LoadScene()
{
	{
		GameObjectManager::GetInstance().ClearWaitingQueue();
		ColliderManager<Collider2D>::GetInstance().ClearCollider();
		ColliderManager<Collider3D>::GetInstance().ClearCollider();
		nextScene = std::make_unique<T>();
		nextFlg = true;
	}
}
