#pragma once



/**
* @file		アプリケーションクラスを作る
*/


#include <Windows.h>
#include <iostream>
#include "../99-Lib/01-MyLib/02-Renderer/98-RendererManager/RendererManager.h"
#include "../99-Lib/01-MyLib/01-System/System.h"
#include "../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"


class HF_Window;

class Application
{
private:
	HINSTANCE hInstance;	//アプリケーションID
	int nCmdShow;
	HF_Window* p_window;	//ウィンドウ

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
	HINSTANCE GetHInstance() const { return hInstance; }
	int GetNCmdShow() const { return nCmdShow; }
	HF_Window* GetWindowPtr() { return p_window; }
	hft::HFFLOAT2 GetWindowSize();

	/**
	* @brief	アプリケーションを継続できるかどうか
	*/
	bool isLoop();

	void Init(HINSTANCE _hInstance, int _nCmdShow);
	int UnInit();
	void Run();
};