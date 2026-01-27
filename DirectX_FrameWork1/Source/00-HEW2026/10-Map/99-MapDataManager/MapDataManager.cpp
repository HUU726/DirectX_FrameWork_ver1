#include "MapDataManager.h"

#include "../00-BaseMap/BaseMap.h"
#include "../Map.h"

MapDataManager::MapDataManager()
{
	mapID = 0;
	datas.resize(MAP_ID::MAX_ID);
}

void MapDataManager::SetMapData(int _id, const MapData& _data)
{
	if (_id < MAP_ID::MAX_ID && _id > 0)
		datas[_id] = _data;
}


BaseMap* MapDataManager::LoadMap()
{

	switch (mapID)
	{
	case MAP_ID::MAP0: p_curMap = new Map0; break;
	case MAP_ID::MAP1: p_curMap = new Map1; break;
	case MAP_ID::MAP2: p_curMap = new Map2; break;
	case MAP_ID::MAP3: p_curMap = new Map3; break;
	case MAP_ID::MAP4: p_curMap = new Map4; break;
	case MAP_ID::MAP5: p_curMap = new Map5; break;
	case MAP_ID::MAP6: p_curMap = new Map6; break;
	case MAP_ID::MAP7: p_curMap = new Map7; break;
	case MAP_ID::MAP8: p_curMap = new Map8; break;
	case MAP_ID::MAP9: p_curMap = new Map9; break;
	default: p_curMap = new Map0; break;
	}

	if (p_curMap)
		p_curMap->Init();
	
	return p_curMap;
}

void MapDataManager::UnInit()
{
	if (p_curMap)
		delete p_curMap;

	std::vector<MapData> swapDatas;
	datas.swap(swapDatas);
}