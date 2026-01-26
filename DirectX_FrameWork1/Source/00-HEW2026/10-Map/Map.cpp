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
	id = 1;
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
	id = 2;
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
	id = 3;
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
	id = 4;
	width = 5;
	height = 5;

	mapDataArray = {
		{ 3,0,0,5,3 },
		{ 0,3,0,0,0 },
		{ 0,0,1,0,0 },
		{ 5,3,0,0,0 },
		{ 5,0,2,0,2 },
	};

	InitBiteEnemyVec({ 2,2 });
	InitGunEnemyVec({ 1,2,2,0 });
}

void Map5::CreateMap()
{
	id = 5;
	width = 7;
	height = 7;

	mapDataArray = {
		{ 0,0,0,2,0,0,0 },
		{ 0,0,0,0,2,0,0 },
		{ 0,2,0,5,0,0,0 },
		{ 0,0,0,0,0,0,2 },
		{ 0,0,4,0,0,0,0 },
		{ 0,0,0,0,0,4,0 },
		{ 5,0,1,0,0,0,0 },
	};

	InitBiteEnemyVec({ 3,1,2,2 });
}

void Map6::CreateMap()
{
	id = 6;
	width = 7;
	height = 7;

	mapDataArray = {
		{ 0,3,0,4,0,3,0 },
		{ 0,0,0,0,0,0,0 },
		{ 4,0,2,0,2,0,0 },
		{ 0,0,0,0,0,0,3 },
		{ 0,0,1,0,0,0,0 },
		{ 3,5,0,0,0,4,0 },
		{ 0,0,4,0,0,5,5 },
	};

	InitBiteEnemyVec({ 3,2 });
	InitGunEnemyVec({ 3,1,1,0 });
}

void Map7::CreateMap()
{
	id = 7;
	width = 7;
	height = 7;

	mapDataArray = {
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}

void Map8::CreateMap()
{
	id = 8;
	width = 7;
	height = 7;

	mapDataArray = {
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}

void Map9::CreateMap()
{
	id = 9;
	width = 7;
	height = 7;

	mapDataArray = {
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}

void Map10::CreateMap()
{
	id = 10;
	width = 7;
	height = 7;

	mapDataArray = {
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
	};

	InitBiteEnemyVec({ 0,1,2,3 });
	InitGunEnemyVec({ 2,1,3 });
}