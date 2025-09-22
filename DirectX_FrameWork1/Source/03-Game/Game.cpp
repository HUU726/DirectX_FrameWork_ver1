#include "Game.h"

#include "../99-Lib/01-MyLib/01-System/System.h"



void Game::Update()
{

}

void Game::Draw()
{
	static System& system = System::GetInstance();
	system.ClearScreen();



	system.SwapChain();
}


Game::Game()
{

}

Game::~Game()
{
}


void Game::Init()
{
}

void Game::Run()
{
	Update();
	Draw();
}

void Game::Uninit()
{
	
}