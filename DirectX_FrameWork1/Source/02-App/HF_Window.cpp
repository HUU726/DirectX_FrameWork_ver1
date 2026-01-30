#include "HF_Window.h"

#include "Application.h"

#include <Windows.h>
#include <ShellScalingApi.h>
#pragma comment(lib, "Shcore.lib")



// 関数のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


/**
* @brief	ウィンドウクラスの初期化＆OSへ転送
* @note		設計図を作成
*/
void HF_Window::InitClass()
{
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	// ウィンドウクラス情報をまとめる
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = Application::GetInstance().GetHInstance();
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;
	RegisterClassEx(&wc);
}

/**
* @brief	ウィンドウを初期化＆描画
* @note		InitClass関数で作った設計図をもとにウィンドウを作成
*/
void HF_Window::InitWindow()
{

	HMONITOR hMonitor = MonitorFromPoint({ 0,0 }, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFO mi = { sizeof(MONITORINFO) };
	GetMonitorInfo(hMonitor, &mi);

	width = mi.rcMonitor.right - mi.rcMonitor.left;
	height = mi.rcMonitor.bottom - mi.rcMonitor.top;

	// ウィンドウの情報をまとめる
	hWnd = CreateWindowEx(0,	// 拡張ウィンドウスタイル
		CLASS_NAME,				// ウィンドウクラスの名前
		WINDOW_NAME,			// ウィンドウの名前
		WS_POPUP | WS_VISIBLE,	// ウィンドウスタイル    WS_OVERLAPPEDWINDOW フレーム付きウィンドウ    WS_POPUP | WS_VISIBLE ボーダーレスウィンドウ
		0,		// ウィンドウの左上Ｘ座標
		0,		// ウィンドウの左上Ｙ座標 
		width/2,					// ウィンドウの幅
		height/2,					// ウィンドウの高さ
		NULL,					// 親ウィンドウのハンドル
		NULL,					// メニューハンドルまたは子ウィンドウID
		Application::GetInstance().GetHInstance(),	// インスタンスハンドル
		NULL);					// ウィンドウ作成データ

	SetWindowPos(
		hWnd,
		HWND_TOP,
		0,
		0,
		width,
		height,
		SWP_FRAMECHANGED
	);

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, Application::GetInstance().GetNCmdShow());
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);
}

HWND HF_Window::GetHWND()
{
	return hWnd;
}

MSG HF_Window::GetMsg()
{
	return message;
}

void HF_Window::Init()
{
	InitClass();
	InitWindow();
}

/**
* @brief	ウィンドウプロシージャ―をマイフレーム更新
*/
bool HF_Window::Update()
{
	// 新たにメッセージがあれば
	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		// ウィンドウプロシージャにメッセージを送る
		DispatchMessage(&message);

		// 「WM_QUIT」メッセージを受け取ったらループを抜ける
		if (message.message == WM_QUIT) {
			return false;
		}
	}

	return true;
}

void HF_Window::UnInit()
{
	UnregisterClass(CLASS_NAME, Application::GetInstance().GetHInstance());
}

void HF_Window::EditWindowName()
{
	//SetWindowTextA(hWnd, CLASS_NAME);
}

void HF_Window::EndWindow()
{
	int res = MessageBoxA(NULL, "終了しますか？", "確認", MB_OKCANCEL);
	if (res == IDOK) {
		DestroyWindow(hWnd);  // 「WM_DESTROY」メッセージを送る
	}
}





//--------------------------------------------------------------------------------------
//ウィンドウプロシージャ
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// 「WM_QUIT」メッセージを送る　→　アプリ終了
		break;

	case WM_CLOSE:  // 「x」ボタンが押されたら
	{
		int res = MessageBoxA(NULL, "終了しますか？", "確認", MB_OKCANCEL);
		if (res == IDOK) {
			DestroyWindow(hWnd);  // 「WM_DESTROY」メッセージを送る
		}
	}
	break;

	case WM_KEYDOWN: //キー入力があったメッセージ
		if (LOWORD(wParam) == VK_ESCAPE)
		{ //入力されたキーがESCAPEなら
			PostMessage(hWnd, WM_CLOSE, wParam, lParam);//「WM_CLOSE」を送る
		}

	default:
		// 受け取ったメッセージに対してデフォルトの処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}