#include "03_GameScene.h"

#include "../10-Map/99-MapDataManager/MapDataManager.h"
#include "../02-UI/UIManager.h"

void Hew_GameScene::Init()
{
	auto& mapMng = MapDataManager::GetInstance();
	const auto& map = mapMng.LoadMap();

	_UI.Init();
}

void Hew_GameScene::UnInit()
{
}
