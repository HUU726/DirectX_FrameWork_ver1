#include "Game.h"

#include "../99-Lib/01-MyLib/01-System/System.h"

#include "../99-Lib/01-MyLib/08-Scene/02-SceneManager/SceneManager.h"



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