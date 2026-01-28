#include "03_GameScene.h"

#include "../10-Map/99-MapDataManager/MapDataManager.h"

void Hew_GameScene::Init()
{
	auto& mapMng = MapDataManager::GetInstance();
	const auto& map = mapMng.LoadMap();
}

void Hew_GameScene::UnInit()
{
}
