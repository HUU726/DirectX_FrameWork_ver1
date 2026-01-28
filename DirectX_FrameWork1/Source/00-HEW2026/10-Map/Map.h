#pragma once

#include "../10-Map/00-BaseMap/BaseMap.h"


enum MAP_ID
{
	MAP0 = 0,
	MAP1,
	MAP2,
	MAP3,
	MAP4,
	MAP5,
	MAP6,
	MAP7,
	MAP8,
	MAP9,
	MAP10,
	MAX_ID,
};


class Map0 : public BaseMap
{
	void CreateMap() override;
};

class Map1 : public BaseMap
{
	void CreateMap() override;
};

class Map2 : public BaseMap
{
	void CreateMap() override;
};

class Map3 : public BaseMap
{
	void CreateMap() override;
};

class Map4 : public BaseMap
{
	void CreateMap() override;
};

class Map5 : public BaseMap
{
	void CreateMap() override;
};

class Map6 : public BaseMap
{
	void CreateMap() override;
};

class Map7 : public BaseMap
{
	void CreateMap() override;
};

class Map8 : public BaseMap
{
	void CreateMap() override;
};

class Map9 : public BaseMap
{
	void CreateMap() override;
};