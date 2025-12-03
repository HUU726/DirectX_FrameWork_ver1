#include "Game.h"

#include "../02-App/Application.h"
#include "../99-Lib/01-MyLib/02-Renderer/98-RendererManager/RendererManager.h"
#include "../99-Lib/01-MyLib/08-Scene/02-SceneManager/SceneManager.h"
#include "../99-Lib/01-MyLib/101-Time/Time.h"


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
* @brief	ƒQ[ƒ€ƒ‹[ƒv
* @note		SceneManager/System‚Ì‰Šú‰»
*/
void Game::Run()
{
	SceneManager& sceneMng = SceneManager::GetInstance();
	Application& app = Application::GetInstance();
	System& system = System::GetInstance();
	Time& time = Time::GetInstance();

	while (app.isLoop())
	{
		if (!time.Update())
		{
			sceneMng.ChangeScene();
			system.GameLoopPipeline();
		}
	}
	
}