#pragma once

#include <string>
#include <vector>


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
	int mapNum;
	std::vector<MapData> datas;

	MapDataManager();


public:
	static MapDataManager& GetInstance()
	{
		static MapDataManager instance;
		return instance;
	}

	void SetMapData(int _id, const MapData& _data);
	const MapData& GetMapData(int _id) { return datas[_id]; }

	void UnInit();

};