#pragma once

#include "../02-Renderer/98-RendererManager/RendererManager.h"
#include "../06-GameObject/999-GameObjectManager/GameObjectManager.h"

class Base_ComponentManager;

class System
{
private:
	RendererManager& rendererMng = RendererManager::GetInstance();
	GameObjectManager& gameObjMng = GameObjectManager::GetInstance();
	std::vector<Base_ComponentManager*> compMngers;
	
	System();

public:
	static System& GetInstance()
	{
		static System instance;
		return instance;
	}

	void AddCompMng(Base_ComponentManager* _p_compMng);

	void Init();
	void ActionComponentMng();
	void UnInit();

};