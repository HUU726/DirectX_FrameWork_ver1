#include "Map.h"

//mapDataArray = {
//	{ 0,0,0,0,0 },
//	{ 0,0,0,0,0 },
//	{ 0,0,0,0,0 },
//	{ 0,0,0,0,0 },
//	{ 0,0,0,0,0 },
//};


// EMPTY		0
// PLAYER		1
// BITE_ENEMY	2
// GUN_ENEMY	3
// BOMB_ENEMY	4
// CONNECT_OBJ	5
// THORM_OBJ	6


void Map1::CreateMap()
{
	width = 5;
	height = 5;

	mapDataArray = {
		{ 0,2,0,0,0 },
		{ 0,0,0,5,0 },
		{ 0,0,1,0,0 },
		{ 2,0,0,2,0 },
		{ 0,0,0,0,5 },
	};

	InitBiteEnemyVec({ 0,2,2 });
}

void Map2::CreateMap()
{
	width = 5;
	height = 5;

	mapDataArray = {
		{ 0,0,2,0,0 },
		{ 0,2,0,5,0 },
		{ 0,0,1,0,0 },
		{ 5,2,0,2,0 },
		{ 0,0,2,0,5 },
	};

	InitBiteEnemyVec({ 2,1,0,1,2 });
}

void Map3::CreateMap()
{
	width = 5;
	height = 5;

	mapDataArray = {
	{ 2,0,3,0,5 },
	{ 0,0,0,0,0 },
	{ 2,5,0,0,3 },
	{ 5,0,1,0,0 },
	{ 0,3,0,0,0 },
	};

	InitBiteEnemyVec({ 0,3 });
	InitGunEnemyVec({ 2,2,1 });
}

void Map4::CreateMap()
{
	width = 5;
	height = 5;

	mapDataArray = {
		{ 0,2,0,0,1 },
		{ 0,1,0,0,0 },
		{ 0,0,1,0,0 },
		{ 2,0,0,0,2 },
		{ 0,1,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}

void Map5::CreateMap()
{
	width = 5;
	height = 5;

	mapDataArray = {
		{ 0,2,0,0,1 },
		{ 0,1,0,0,0 },
		{ 0,0,1,0,0 },
		{ 2,0,0,0,2 },
		{ 0,1,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}

void Map6::CreateMap()
{
	width = 5;
	height = 5;

	mapDataArray = {
		{ 0,2,0,0,1 },
		{ 0,1,0,0,0 },
		{ 0,0,1,0,0 },
		{ 2,0,0,0,2 },
		{ 0,1,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}

void Map7::CreateMap()
{
	width = 5;
	height = 5;

	mapDataArray = {
		{ 0,2,0,0,1 },
		{ 0,1,0,0,0 },
		{ 0,0,1,0,0 },
		{ 2,0,0,0,2 },
		{ 0,1,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}

void Map8::CreateMap()
{
	width = 5;
	height = 5;

	mapDataArray = {
		{ 0,2,0,0,1 },
		{ 0,1,0,0,0 },
		{ 0,0,1,0,0 },
		{ 2,0,0,0,2 },
		{ 0,1,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}

void Map9::CreateMap()
{
	width = 5;
	height = 5;

	mapDataArray = {
		{ 0,2,0,0,1 },
		{ 0,1,0,0,0 },
		{ 0,0,1,0,0 },
		{ 2,0,0,0,2 },
		{ 0,1,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}

void Map10::CreateMap()
{
	width = 5;
	height = 5;

	mapDataArray = {
		{ 0,2,0,0,1 },
		{ 0,1,0,0,0 },
		{ 0,0,1,0,0 },
		{ 2,0,0,0,2 },
		{ 0,1,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}