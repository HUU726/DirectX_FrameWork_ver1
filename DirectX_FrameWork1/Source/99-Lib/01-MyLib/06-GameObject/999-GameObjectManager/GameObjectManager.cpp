#include "GameObjectManager.h"



void GameObjectManager::AddGameObject(GameObject* _p_gameObject)
{
	idCnt++;
	_p_gameObject->SetID(idCnt);
	gameObjects.push_back(_p_gameObject);
}

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
	for (auto& gameObject : gameObjects)
		gameObject->Update();
}