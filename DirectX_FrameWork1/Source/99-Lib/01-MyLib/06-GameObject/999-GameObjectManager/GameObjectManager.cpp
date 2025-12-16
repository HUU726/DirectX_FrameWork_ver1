#include "GameObjectManager.h"

#include "../GameObject.h"
#include "../../08-Scene/02-SceneManager/SceneManager.h"

/*
* @note		GameObjectのコンストラクタで呼出し
*/
void GameObjectManager::AddGameObject(GameObject* _p_gameObject)
{
	if (!SceneManager::GetInstance().GetNext())
	{
		idCnt++;
		_p_gameObject->SetID(idCnt);
		waitingQueue.push_back(_p_gameObject);
	}
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

void GameObjectManager::SetUpObject()
{
	gameObjects.clear();
	waitingQueue.swap(gameObjects);
}
void GameObjectManager::Clear()
{
	gameObjects.clear();
}

void GameObjectManager::ClearWaitingQueue()
{
	waitingQueue.clear();
}

void GameObjectManager::AddWaitToNow()
{
	if ( waitingQueue.size() && !SceneManager::GetInstance().GetNext() )
	{
		gameObjects.insert(gameObjects.end(), waitingQueue.begin(), waitingQueue.end());
		waitingQueue.clear();
	}
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