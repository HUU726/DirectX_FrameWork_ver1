#include "Application.h"

#include "HF_Window.h"
#include "../03-Game/Game.h"

#include "../04-Input/Input.h"	//朝日奈担当の入力系クラス

Application::Application()
{
	p_window = nullptr;
}
void Application::CreateConsole()
{
	FILE* p_fl;
	AllocConsole();  // コンソールを割り当て
	freopen_s(&p_fl, "CONOUT$", "w", stdout);  // 標準出力をリダイレクト
	std::cout << "DirectX 11 + Console initialized!" << std::endl;
}
void Application::InitWindow()
{
	p_window = new HF_Window;
	p_window->Init();
}
void Application::InitSystem()
{
	HWND hWnd = p_window->GetHWND();
	System::GetInstance().Init(hWnd);
	Input::GetInstance().Init(hWnd); //朝日奈担当の入力システム初期化
}

bool Application::isLoop()
{
	return p_window->Update();
}

void Application::Init(HINSTANCE _hInstance, int _nCmdShow)
{
	hInstance = _hInstance;
	nCmdShow = _nCmdShow;
	CreateConsole();
	InitWindow();
	InitSystem();
}
int Application::UnInit()
{
	int l_result = int(p_window->GetMsg().wParam);

	System::GetInstance().UnInit();
	Input::GetInstance().Uninit(); //朝日奈担当の入力システム終了
	p_window->UnInit();
	delete p_window;

	return l_result;
}
void Application::Run()
{
	Game& game = Game::GetInstance();
	game.Init();	//ゲーム初期化
	game.Run();		//ゲームループ
	game.Uninit();	//ゲーム終了処理
}