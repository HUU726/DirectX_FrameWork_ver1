#include "GameObjectManager.h"

#include "../GameObject.h"

/*
* @note		GameObjectのコンストラクタで呼出し
*/
void GameObjectManager::AddGameObject(GameObject* _p_gameObject)
{
	idCnt++;
	_p_gameObject->SetID(idCnt);
	gameObjects.push_back(_p_gameObject);
}

/**
* @note		GameObjectのデストラクタで呼び出し
*/
void GameObjectManager::RemoveGameObject(GameObject* _p_gameObject)
{
	auto it = std::find(gameObjects.begin(),gameObjects.end(), _p_gameObject);

	if ( it != gameObjects.end())
	{
		gameObjects.erase(it);
	}
}

void GameObjectManager::Clear()
{
	gameObjects.clear();
}


void GameObjectManager::Action()
{
	int cnt = 0;
	for (auto& gameObject : gameObjects)
	{
		cnt++;
		gameObject->Update();
	}
}