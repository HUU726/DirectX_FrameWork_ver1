#pragma once

#undef UNICODE  // Unicodeではなく、マルチバイト文字を使う
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

// マクロ定義
#define CLASS_NAME   "DX21_Fuki"// ウインドウクラスの名前
#define WINDOW_NAME  "FH_Application"// ウィンドウの名前

#define SCREEN_WIDTH (1920 / 1.5)		//ウィンドウ横
#define SCREEN_HEIGHT (1080 / 1.5)	//ウィンドウ縦



class HF_Window
{
private:
	float width;
	float height;
	HWND hWnd;
	MSG message;

	void InitClass();
	void InitWindow();

public:
	/*** ゲッター ***/
	HWND GetHWND();
	MSG GetMsg();
	float GetWidth() { return width; }
	float GetHeight() { return height; }

	void Init();
	bool Update();
	void UnInit();

	/**
	* @brief	ウィンドウの名前を変更
	*/
	void EditWindowName();

};

