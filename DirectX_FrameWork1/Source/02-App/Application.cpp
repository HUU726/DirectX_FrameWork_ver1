#include "Application.h"

#include "FH_Window.h"
#include "../99-Lib/01-MyLib/101-Time/Time.h"
#include "../03-Game/Game.h"


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
	p_window = new FH_Window;
	p_window->Init();
}

void Application::InitSystem()
{
	HWND hWnd = p_window->GetHWND();
	system.Init(hWnd);
}

void Application::Init(HINSTANCE _hInstance, int _nCmdShow)
{
	hInstance = _hInstance;
	nCmdShow = _nCmdShow;
	InitWindow();
	InitSystem();
	CreateConsole();

	Time::GetInstance().SetFps(60);
}

void Application::Run()
{
	static Game& game = Game::GetInstance();
	game.Init();

	while (true)
	{
		if (!p_window->Update())
			break;

		if (!Time::GetInstance().Update())
			game.Run();

		

	}

	game.Uninit();

}

int Application::UnInit()
{
	int l_result = int(p_window->GetMsg().wParam);

	system.UnInit();
	p_window->UnInit();
	delete p_window;

	return l_result;
}
