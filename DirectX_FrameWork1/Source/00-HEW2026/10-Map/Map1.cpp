#include "Map1.h"

void Map1::CreateMap()
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
