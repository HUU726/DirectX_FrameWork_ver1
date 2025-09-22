#include "FH_Window.h"

#include "Application.h"


// 関数のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



void FH_Window::InitClass()
{
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

void FH_Window::InitWindow()
{
	// ウィンドウの情報をまとめる
	hWnd = CreateWindowEx(0,	// 拡張ウィンドウスタイル
		CLASS_NAME,				// ウィンドウクラスの名前
		WINDOW_NAME,			// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	// ウィンドウスタイル
		CW_USEDEFAULT,			// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,			// ウィンドウの左上Ｙ座標 
		SCREEN_WIDTH,			// ウィンドウの幅
		SCREEN_HEIGHT,			// ウィンドウの高さ
		NULL,					// 親ウィンドウのハンドル
		NULL,					// メニューハンドルまたは子ウィンドウID
		Application::GetInstance().GetHInstance(),	// インスタンスハンドル
		NULL);					// ウィンドウ作成データ

	// ウィンドウのサイズを修正
	RECT rc1, rc2;
	GetWindowRect(hWnd, &rc1);	//ウィンドウの短形領域を取得
	GetClientRect(hWnd, &rc2);	//クライアントの短形領域を取得
	int sx = SCREEN_WIDTH;
	int sy = SCREEN_HEIGHT;
	sx += ((rc1.right - rc1.left) - (rc2.right - rc2.left));
	sy += ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top));
	SetWindowPos(hWnd, NULL, 0, 0, sx, sy, (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, Application::GetInstance().GetNCmdShow());
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);
}

HWND FH_Window::GetHWND()
{
	return hWnd;
}

MSG FH_Window::GetMsg()
{
	return message;
}

void FH_Window::Init()
{
	InitClass();
	InitWindow();
}

bool FH_Window::Update()
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

void FH_Window::UnInit()
{
	UnregisterClass(CLASS_NAME, Application::GetInstance().GetHInstance());
}

void FH_Window::EditWindowName()
{
}

//wsprintfA(str, "FPS=%d", fpsCounter);
//SetWindowTextA(hWnd, str);



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