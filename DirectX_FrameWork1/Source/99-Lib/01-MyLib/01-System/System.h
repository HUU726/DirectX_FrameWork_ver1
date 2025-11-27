#pragma once

#include "../02-Renderer/98-RendererManager/RendererManager.h"
#include "../06-GameObject/999-GameObjectManager/GameObjectManager.h"

class IF_ComponentManager;

class System
{
private:
	RendererManager& rendererMng = RendererManager::GetInstance();
	GameObjectManager& gameObjMng = GameObjectManager::GetInstance();
	std::vector<IF_ComponentManager*> compMngs;
	
	System();

	void InputCompMngAction();
	void GameObjectMngAction();
	void BeforeRender_CompMngsAction();
	void RendererCompMngAction();

public:
	static System& GetInstance()
	{
		static System instance;
		return instance;
	}

	void AddCompMng(IF_ComponentManager* _p_compMng);

	void InitSystem(HWND _hwnd);
	void UnInitSystem();

	void GameLoopPipeline();
	void ClearManagersData();

};