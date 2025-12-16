#include "BaseMap.h"

#include "../../01-GamaeObject/01-TrackObject/00-TrackObject/TrackObject.h"
#include "../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"


#define MAP_CENTER_POSX (0)
#define MAP_CENTER_POSY (0)
#define TILE_SCALEX (100.0f)
#define TILE_SCALEY (100.0f)
#define TILE_SCALEX_HALF (TILE_SCALEX / 2.0f)
#define TILE_SCALEY_HALF (TILE_SCALEY / 2.0f)

void Debug_TilePaintColor_FromXY(hft::HFFLOAT2 _index, GameObject* _obj, hft::HFFLOAT2 _moveVec)
{
	if (_moveVec.y)
	{
		switch (static_cast<int>(_index.y))
		{
		case 1:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,0,0,1 };
			break;
		case 2:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 0,1,0,1 };
			break;
		case 3:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 0,0,1,1 };
			break;
		case 4:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,1,0,1 };
			break;
		case 5:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,0,1,1 };
			break;
		case 6:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 0,1,1,1 };
			break;
		default:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,1,1,1 };
			break;
		}
	}
	else if (_moveVec.x)
	{
		switch (static_cast<int>(_index.x))
		{
		case 1:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,0,0,1 };
			break;
		case 2:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 0,1,0,1 };
			break;
		case 3:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 0,0,1,1 };
			break;
		case 4:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,1,0,1 };
			break;
		case 5:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,0,1,1 };
			break;
		case 7:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 0,1,1,1 };
			break;
		default:
			_obj->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,1,1,1 };
			break;
		}
	}
}
void Debug_TilePaintColor_FromTile(int _index, std::vector<TrackObject*>& _objects)
{
	_objects[_index]->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,0,0,1 };
}

void BaseMap::Slide()
{
	static int downFlame = 60;

	for (auto& data : slideDatas)
	{
		SearchOnLineTiles(data);
		SlideTileObject(data);
		SearchOnLineObjects(data);
		SlideTrackObject(data);
		std::cout << data.power << std::endl;
		if (data.cntFlame > downFlame )
		{
			data.power *= 0.8;
			data.cntFlame = 0;
		}
		else
		{
			data.cntFlame++;
		}
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

void BaseMap::SearchOnLineTiles(SlideData& _data)
{
	_data.trackObjects.clear();

	for ( const auto& obj : tileObjects )
	{
		if ( _data.moveVec.x )
		{
			if ( obj->GetLineIndex().y == _data.anchorPos.y )
				_data.trackObjects.push_back(obj);
		}
		else if ( _data.moveVec.y )
		{
			if ( obj->GetLineIndex().x == _data.anchorPos.x )
				_data.trackObjects.push_back(obj);
		}
	}
}

void BaseMap::SlideTileObject(SlideData& _data)
{
	_data.changeFlg = false;
	for ( auto obj : _data.trackObjects )
	{
		Transform* p_trf = obj->GetTransformPtr();
		p_trf->position += _data.moveVec * _data.power * Time::GetInstance().DeltaTime();

		if ( _data.moveVec.x)
		{
			if ( p_trf->position.x > rightBottomPos.x  || p_trf->position.x < leftTopPos.x - TILE_SCALEX )
			{
				p_trf->position.x -= TILE_SCALEX * width * _data.moveVec.x;
				_data.changeFlg = true;
			}
		}
		else if ( _data.moveVec.y )
		{
			if ( p_trf->position.y > leftTopPos.y + TILE_SCALEY || p_trf->position.y < rightBottomPos.y )
			{
				p_trf->position.y -= TILE_SCALEY * height * _data.moveVec.y;
				_data.changeFlg = true;
			}
		}


	}

	if ( _data.changeFlg )
	{
		for ( auto obj : _data.trackObjects )
		{
			hft::HFFLOAT2 index = obj->GetLineIndex();
			if ( _data.moveVec.x )
				index += _data.moveVec;
			else if ( _data.moveVec.y )
				index -= _data.moveVec;

			if ( index.x < 0 || index.x > width - 1 )
				index.x -= (width ) * _data.moveVec.x;
			else if ( index.y < 0 || index.y > height - 1 )
				index.y += (height) * _data.moveVec.y;
			
			obj->SetLineIndex(index);

			//Debug_TilePaintColor_FromXY(index, obj, _data.moveVec);
		}

		Debug_TilePaintColor_FromTile(18, tileObjects);

		if ( _data.power < 40 )
			_data.power = 0;

	}

}

void BaseMap::SearchOnLineObjects(SlideData& _data)
{
	_data.trackObjects.clear();

	for (const auto& obj : onMapTrackObjects)
	{
		if (_data.moveVec.x)
		{
			if (obj->GetLineIndex().y == _data.anchorPos.y)
				_data.trackObjects.push_back(obj);
		}
		else if (_data.moveVec.y)
		{
			if (obj->GetLineIndex().x == _data.anchorPos.x)
				_data.trackObjects.push_back(obj);
		}
	}
}

void BaseMap::SlideTrackObject(SlideData& _data)
{
	for (auto obj : _data.trackObjects)
	{
		Transform* p_trf = obj->GetTransformPtr();
		p_trf->position += _data.moveVec * _data.power * Time::GetInstance().DeltaTime();
	}
}

BaseMap::BaseMap()
{
	p_transform->position.x = MAP_CENTER_POSX;
	p_transform->position.y = MAP_CENTER_POSY;
}

BaseMap::~BaseMap()
{
	for ( int i = 0; i < tileObjects.size(); i++ )
	{
		delete tileObjects.at(i);
	}
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
	width = _width + 2;
	height = _height + 2;

	int tileNum = height * width;
	for (int i = 0; i < tileNum; i++)
	{
		auto tileObject = new	TrackObject;
		auto renderer = tileObject->GetComponent<SpriteRenderer>();
		renderer->LoadTexture("Assets/01-Texture/99-Test/Tile.jpg");
		tileObject->GetTransformPtr()->scale = { TILE_SCALEX,TILE_SCALEY };
		tileObjects.push_back(tileObject);
	}

	leftTopPos.x = MAP_CENTER_POSX - (width / 2.0f * TILE_SCALEX) + TILE_SCALEX_HALF;
	leftTopPos.y = MAP_CENTER_POSY + (height / 2.0f * TILE_SCALEY) - TILE_SCALEY_HALF;
	rightBottomPos.x = leftTopPos.x + (width * TILE_SCALEX);
	rightBottomPos.y = leftTopPos.y - (height * TILE_SCALEY);

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
	{
		SetSlideData(hft::HFFLOAT2(5, 1), hft::HFFLOAT2(1, 0), 100);
		SetSlideData(hft::HFFLOAT2(5, 2), hft::HFFLOAT2(-1, 0), 100);
	}

	if ( GetAsyncKeyState('O') & 0x0001 )
	{
		SetSlideData(hft::HFFLOAT2(5, 1), hft::HFFLOAT2(-1, 0), 100);
		SetSlideData(hft::HFFLOAT2(5, 2), hft::HFFLOAT2(1, 0), 100);
	}

	if ( GetAsyncKeyState('U') & 0x0001 )
	{
		SetSlideData(hft::HFFLOAT2(4, 3), hft::HFFLOAT2(0, 1), 300);
		SetSlideData(hft::HFFLOAT2(5, 3), hft::HFFLOAT2(0, -1), 300);
	}


	Slide();
}
