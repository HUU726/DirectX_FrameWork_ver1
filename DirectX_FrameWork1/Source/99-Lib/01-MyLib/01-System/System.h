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

	/**
	* @brief	マネージャー登録
	*/
	void AddCompMng(IF_ComponentManager* _p_compMng);
	/**
	* @brief	各種マネージャー開放
	*/
	void ClearManagersData();

	/**
	* @brief	Systemクラス初期化
	* @param	HWND	_hwnd	ウィンドウのハンドル
	*/
	void Init(HWND _hwnd);
	/**
	* @brief	Systemクラス終了処理
	*/
	void UnInit();
	/**
	* @brief	ゲームループ内処理
	* @note		Scene/GameObject/Componentなどの処理順を制御
	*/
	void GameLoopPipeline();

};