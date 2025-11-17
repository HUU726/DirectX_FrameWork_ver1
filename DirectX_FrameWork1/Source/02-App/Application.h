#pragma once


/***************************************************************************************************
*				インクルード
***************************************************************************************************/
#include <Windows.h>
#include <iostream>
#include "../99-Lib/01-MyLib/02-Renderer/98-RendererManager/RendererManager.h"

/***************************************************************************************************
*				マクロ
***************************************************************************************************/





class HF_Window;

class Application
{
private:
	HINSTANCE hInstance;	//アプリケーションID
	int nCmdShow;
	HF_Window* p_window;	//ウィンドウ
	RendererManager& rendererMng = RendererManager::GetInstance();


	void InitWindow();
	void InitSystem();
	void CreateConsole();
	Application();

public:

	static Application& GetInstance()
	{
		static Application instance;
		return instance;
	}
	HINSTANCE GetHInstance() { return hInstance; }
	int GetNCmdShow() { return nCmdShow; }

	void Init(HINSTANCE _hInstance, int _nCmdShow);
	void Run();
	int UnInit();
};

