#include "Game.h"

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
	SceneManager& sceneMng = SceneManager::GetInstance();
	sceneMng.Init();

	Time::GetInstance().SetFps(60);
}

void Game::Run()
{
	static SceneManager& sceneMng = SceneManager::GetInstance();

	sceneMng.RunScene();
}

void Game::Uninit()
{
	SceneManager& sceneMng = SceneManager::GetInstance();
	sceneMng.UnInit();
}