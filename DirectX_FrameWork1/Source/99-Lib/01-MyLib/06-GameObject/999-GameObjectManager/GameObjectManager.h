#pragma once

#include "../GameObject.h"

class GameObjectManager
{
private:
	int idCnt;
	std::vector<GameObject*> gameObjects;

	GameObjectManager();

public:
	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}

	void AddGameObject(GameObject* _p_gameObject);
	void DestroyObject(GameObject* _p_gameObject);
	void Clear();

};

