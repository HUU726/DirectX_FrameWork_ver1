#pragma once

#include <string>
#include <vector>

class BaseMap;

//外部に放出するマップデータ
struct MapData
{
	int id;
	bool clearFlg;
	float clearTime;
	int playerHP;	//クリア時のプレイヤーの残り体力
};


class MapDataManager
{
private:
	BaseMap* p_curMap;
	int mapID;
	std::vector<MapData> datas;

	MapDataManager();


public:
	static MapDataManager& GetInstance()
	{
		static MapDataManager instance;
		return instance;
	}

	void SetMapID(int _id) { mapID = _id; }
	void SetMapData(int _id, const MapData& _data);
	const MapData& GetMapData(int _id) { return datas[_id]; }

	BaseMap* LoadMap();

	void UnInit();

};