#include "BaseMap.h"

#include "../../01-GamaeObject/01-TrackObject/00-TrackObject/TrackObject.h"



#define MAP_CENTER_POSX (0)
#define MAP_CENTER_POSY (0)
#define TILE_SCALEX (100.0f)
#define TILE_SCALEY (100.0f)


void BaseMap::Slide()
{
	static int flame = 0;

	if (flame > 120)
	{
		flame++;
	}
	else{
		flame++;
		return;
	}

	for (auto& data : slideDatas)
	{
		SearchOnLineObjects(data);
		SlideTrackObject(data);
		data.power *= 0.8;
		if (data.power < 1)
			data.power = 0;
	}

	for (auto& data : slideDatas)
	{
		if (data.power == 0)
		{
			auto it = std::find(slideDatas.begin(), slideDatas.end(), data);
			if (it != slideDatas.end())
				slideDatas.erase(it);
		}
	}
}

void BaseMap::SearchOnLineObjects(SlideData& _data)
{
	_data.trackObjects.clear();

	for (const auto& obj : onMapTrackObjects)
	{
		if (_data.moveVec.x)
		{
			if (obj->GetLineIndex().y == _data.anchorPos.x)
				_data.trackObjects.push_back(obj);
		}
		else if (_data.moveVec.y)
		{
			if (obj->GetLineIndex().x == _data.anchorPos.y)
				_data.trackObjects.push_back(obj);
		}
	}

}

void BaseMap::SlideTrackObject(SlideData& _data)
{

	for (auto obj : _data.trackObjects)
	{
		Transform* p_trf = obj->GetTransformPtr();
		p_trf->position += _data.moveVec * _data.power;
	}
}

BaseMap::BaseMap()
{
	p_transform->position.x = MAP_CENTER_POSX;
	p_transform->position.y = MAP_CENTER_POSY;
}


void BaseMap::SetSlideData(const hft::HFFLOAT2& _anchorPos, const hft::HFFLOAT2& _moveVec, const float& _power)
{
	SlideData data{ _anchorPos,_moveVec,_power };
	slideDatas.push_back(data);
}

void BaseMap::Init()
{
}

#include "../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
void BaseMap::Init(const int& _width, const int& _height)
{
	width = _width;
	height = _height;

	int tileNum = height * width;
	for (int i = 0; i < tileNum; i++)
	{
		auto tileObject = new	TrackObject;
		auto renderer = tileObject->GetComponent<SpriteRenderer>();
		renderer->LoadTexture("Assets/01-Texture/99-Test/daruma.jpg");
		tileObject->GetTransformPtr()->scale = { TILE_SCALEX,TILE_SCALEY };
		tileObjects.push_back(tileObject);
		onMapTrackObjects.push_back(tileObject);
	}

	hft::HFFLOAT2 leftTopPos;	//ç∂è„É^ÉCÉãÇÃç¿ïW
	leftTopPos.x = MAP_CENTER_POSX - (width / 2.0f * TILE_SCALEX) + TILE_SCALEX / 2.0f;
	leftTopPos.y = MAP_CENTER_POSY + (height / 2.0f * TILE_SCALEY) - TILE_SCALEX / 2.0f;

	for (int y = 0; y < height; y++)
	{
		int index = y * width;
		float posY = leftTopPos.y - (TILE_SCALEY * y);
		for (int x = 0; x < width; x++)
		{
			float posX = leftTopPos.x + (TILE_SCALEX * x);
			tileObjects.at(index)->GetTransformPtr()->position = { posX,posY };
			tileObjects.at(index)->SetLineIndex(hft::HFFLOAT2(x, y));
			index++;
		}
	}
}

void BaseMap::Update()
{
	if (GetAsyncKeyState('P') & 0x0001)
		SetSlideData(hft::HFFLOAT2(5, 1), hft::HFFLOAT2(1, 0), 100);

	Slide();
}
