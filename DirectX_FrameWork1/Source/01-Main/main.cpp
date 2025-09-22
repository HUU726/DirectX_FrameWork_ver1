#undef UNICODE  // Unicodeではなく、マルチバイト文字を使う
#define _CRT_SECURE_NO_WARNINGS

#include "../02-App/Application.h"




//--------------------------------------------------------------------------------------
// エントリポイント＝一番最初に実行される関数
//--------------------------------------------------------------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	Application& app = Application::GetInstance();
	app.Init(hInstance, nCmdShow);
	std::cout << "Test push" << std::endl;
	app.Run();
	return app.UnInit();;
}