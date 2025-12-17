#include "Game.h"

#include "../02-App/Application.h"
#include "../99-Lib/01-MyLib/02-Renderer/98-RendererManager/RendererManager.h"
#include "../99-Lib/01-MyLib/08-Scene/02-SceneManager/SceneManager.h"
#include "../99-Lib/01-MyLib/101-Time/Time.h"
#include "../04-Input/Input.h"	//朝日奈担当の入力系クラス


Game::Game()
{
}

Game::~Game()
{
}


void Game::Init()
{
	Time::GetInstance().SetFps(60);
}
void Game::Uninit()
{
	SceneManager& sceneMng = SceneManager::GetInstance();
	sceneMng.UnInit();
}


/**
* @brief	ゲームループ
* @note		SceneManager/Systemの初期化
*/
void Game::Run()
{
	SceneManager& sceneMng = SceneManager::GetInstance();
	Application& app = Application::GetInstance();
	System& system = System::GetInstance();
	Time& time = Time::GetInstance();
	Input& input = Input::GetInstance(); //朝日奈担当の入力システム参照

	while (app.isLoop())
	{
		if (!time.Update())
		{
			sceneMng.ChangeScene();
			system.GameLoopPipeline();
			input.Update(); //朝日奈担当の入力システム更新
		}
	}
	
}