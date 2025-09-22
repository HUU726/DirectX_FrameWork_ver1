#include "TitleScene.h"

#include "GameScene.h"


void TitleScene::Init()
{
	
}

void TitleScene::Input()
{

}

void TitleScene::Update()
{
	flameCnt++;
	if (flameCnt > 1000)
		nextScene = std::make_unique<GameScene>();
}

void TitleScene::Draw()
{	

}

void TitleScene::UnInit()
{
}
