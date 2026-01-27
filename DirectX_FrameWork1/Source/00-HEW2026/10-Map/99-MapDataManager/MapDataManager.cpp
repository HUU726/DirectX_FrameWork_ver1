#include "MapDataManager.h"



MapDataManager::MapDataManager()
{
	mapNum = 10;


	datas.resize(mapNum);
}

void MapDataManager::SetMapData(int _id, const MapData& _data)
{
	if (datas.size() < (_id - 1))
	{
		datas.resize(_id);
	}

	datas[_id] = _data;
}

void MapDataManager::UnInit()
{
	std::vector<MapData> swapDatas;
	datas.swap(swapDatas);
}