#include "GameObjectManager.h"

#include "../GameObject.h"
#include "../../08-Scene/02-SceneManager/SceneManager.h"

/*
* @note		GameObjectのコンストラクタで呼出し
*/
void GameObjectManager::AddGameObject(GameObject* _p_gameObject)
{
	if (SceneManager::GetInstance().GetNext() == false)
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

void GameObjectManager::DestroyGameObject(GameObject* _p_gameObject)
{
	_p_gameObject->SetIsActive(false);
	_p_gameObject->SetIsRender(false);
	RemoveGameObject(_p_gameObject);
	destroyQueue.push_back(_p_gameObject);
}

void GameObjectManager::SetUpObject()
{
	std::vector<GameObject*> swapGameObjects;
	swapGameObjects.swap(gameObjects);
	waitingQueue.swap(gameObjects);
}
void GameObjectManager::Clear()
{
	std::vector<GameObject*> swapGameObjects;
	swapGameObjects.swap(gameObjects);
}

void GameObjectManager::ClearWaitingQueue()
{
	std::vector<GameObject*> swapGameObjects;
	swapGameObjects.swap(waitingQueue);
}

void GameObjectManager::ClearDestroyQueue()
{
	if (destroyQueue.size())
	{
		for (int i = 0; i < destroyQueue.size(); i++)
			delete destroyQueue[i];

		std::vector<GameObject*> swapGameObjects;
		swapGameObjects.swap(destroyQueue);
	}
}

void GameObjectManager::AddWaitToNow()
{
	if ( waitingQueue.size() && !SceneManager::GetInstance().GetNext() )
	{
		gameObjects.insert(gameObjects.end(), waitingQueue.begin(), waitingQueue.end());
		std::vector<GameObject*> swapGameObjects;
		swapGameObjects.swap(waitingQueue);
	}
}


void GameObjectManager::Action()
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->Update();
	}
}

std::vector<GameObject*> GameObjectManager::FindGameObject_Tag(std::string _tag)
{
	std::vector<GameObject*> answer;

	for (const auto& gameObject : gameObjects)
	{
		if (gameObject->GetName() == _tag)
			answer.push_back(gameObject);
	}

	return answer;
}

std::vector<GameObject*> GameObjectManager::FindGameObject_Name(std::string _name)
{
	std::vector<GameObject*> answer;

	for (const auto& gameObject : gameObjects)
	{
		if (gameObject->GetName() == _name)
			answer.push_back(gameObject);
	}

	return answer;
}
