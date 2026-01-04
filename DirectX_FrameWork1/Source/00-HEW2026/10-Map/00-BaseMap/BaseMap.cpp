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

	for (auto& data : tileSlideDatas)
	{
		SlideTileObject(data);
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
	for (auto& data : objSlideDatas)
	{
		SlideTrackObject(data);
		if (data.cntFlame > downFlame)
		{
			data.power *= 0.8;
			data.cntFlame = 0;
		}
		else
		{
			data.cntFlame++;
		}
	}

	//ズレる力が０になったらパイプラインから除外
	for (auto& data : tileSlideDatas)
	{
		if (data.power == 0)
		{
			auto it = std::find(tileSlideDatas.begin(), tileSlideDatas.end(), data);
			if (it != tileSlideDatas.end())
				tileSlideDatas.erase(it);
		}
	}
	for (auto& data : tileSlideDatas)
	{
		if (data.power == 0)
		{
			auto it = std::find(tileSlideDatas.begin(), tileSlideDatas.end(), data);
			if (it != tileSlideDatas.end())
				tileSlideDatas.erase(it);
		}
	}
}

void BaseMap::SearchOnLineTiles(SlideData& _data)
{
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
		hft::HFFLOAT2 moveVec = { _data.moveVec.x,_data.moveVec.y * -1 };
		p_trf->position += moveVec * _data.power;


		if ( p_trf->position.x > rightBottomPos.x  || p_trf->position.x < leftTopPos.x - TILE_SCALEX )
		{
			_data.changeFlg = true;
		}
		else if ( p_trf->position.y > leftTopPos.y + TILE_SCALEY || p_trf->position.y < rightBottomPos.y )
		{
			_data.changeFlg = true;
		}
	}

	if ( _data.changeFlg )
	{
		for ( auto obj : _data.trackObjects )
		{
			hft::HFFLOAT2 index = obj->GetLineIndex();
			index += _data.moveVec;
			SetLineIndexToPos(index, *obj);
		}

		if ( _data.power < 1 )
			_data.power = 0;
	}

}

void BaseMap::SearchOnLineObjects(SlideData& _data)
{

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

void BaseMap::SetLineIndexToPos(hft::HFFLOAT2& _index, TrackObject& _obj)
{
	if (_index.x < 0)
		_index.x = width - 1;
	else if (_index.x >= width)
		_index.x = 0;

	if (_index.y < 0)
		_index.y = height - 1;
	else if (_index.y >= height)
		_index.y = 0;

	_obj.SetLineIndex(_index);
	hft::HFFLOAT4& pos = _obj.GetTransformPtr()->position;
	pos = { leftTopPos.x + _index.x * TILE_SCALEX, leftTopPos.y - _index.y * TILE_SCALEY };
}

BaseMap::BaseMap()
{
	p_transform->position.x = MAP_CENTER_POSX;
	p_transform->position.y = MAP_CENTER_POSY;
}


void BaseMap::SetSlideData(const hft::HFFLOAT2& _anchorPos, const hft::HFFLOAT2& _moveVec, const float& _power)
{
	//ズレが存在するか確認
	{
		if (tileSlideDatas.size() <= 0)
		{
			SlideData tileData{ _anchorPos,_moveVec,_power };
			SearchOnLineTiles(tileData);
			tileSlideDatas.push_back(tileData);

			SlideData objData{ _anchorPos,_moveVec,_power };
			SearchOnLineObjects(objData);
			objSlideDatas.push_back(objData);

			return;
		}
	}

	//すでに動いているか確認
	{
		for (auto data : tileSlideDatas)
		{
			if (data.moveVec.x)
			{
				if (data.anchorPos.y == _anchorPos.y)
					return;
			}
			if (data.moveVec.y)
			{
				if (data.anchorPos.x == _anchorPos.x)
					return;
			}
		}
	}

	//クロス確認
	{
		hft::HFFLOAT2 curMoveVec = tileSlideDatas.at(0).moveVec;
		float crossFlg = (_moveVec.x * curMoveVec.y) + (_moveVec.y * curMoveVec.x);
		if (crossFlg)
		{
			hft::HFFLOAT2 moveVecFlg = { (_moveVec.x * _moveVec.x),(_moveVec.y * _moveVec.y) };	//X or Yどっちに動いているかのフラグ
			float moveVec = (_moveVec.x * moveVecFlg.x) + (_moveVec.y * moveVecFlg.y);		//移動方向 ( 1 or -1 )
			float basePos = (_anchorPos.x * moveVecFlg.x) + (_anchorPos.y * moveVecFlg.y);	//基準点
			float changePos = (width * moveVecFlg.x) + (height * moveVecFlg.y);			//マップの、幅or高さ

			//追加するズレの移動方向順に既存ズレとの干渉を「検索」＆「停止・調節」
			for (int i = basePos + moveVec; i != basePos; i += moveVec)
			{
				if (i > changePos)
					i = 0;
				if (i < 0)
					i = changePos;

				for (auto data : tileSlideDatas)
				{
					float ancPos = (data.anchorPos.x * moveVecFlg.x) + (data.anchorPos.y * moveVecFlg.y);
					if (ancPos != i)
						continue;

					if (_power < data.power)
						return;

					auto it = std::find(tileSlideDatas.begin(), tileSlideDatas.end(), data);
					if (it != tileSlideDatas.end())
					{
						//ここで列を綺麗に整える
						for (auto obj : data.trackObjects)
						{
							hft::HFFLOAT2 index = obj->GetLineIndex();
							index -= data.moveVec;
							SetLineIndexToPos(index, *obj);
						}
						tileSlideDatas.erase(it);
					}

				}
			}
		}
	}

	SlideData data{ _anchorPos,_moveVec,_power };
	SearchOnLineTiles(data);
	tileSlideDatas.push_back(data);

	SlideData objData{ _anchorPos,_moveVec,_power };
	SearchOnLineObjects(objData);
	objSlideDatas.push_back(objData);
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
		SetSlideData(hft::HFFLOAT2(1, 6), hft::HFFLOAT2(-1, 0), 3);
	}
	if (GetAsyncKeyState('O') & 0x0001)
	{
		SetSlideData(hft::HFFLOAT2(1, 2), hft::HFFLOAT2(1, 0), 6);
		SetSlideData(hft::HFFLOAT2(1, 3), hft::HFFLOAT2(-1, 0), 2.5);
	}

	if (GetAsyncKeyState('U') & 0x0001)
	{
		SetSlideData(hft::HFFLOAT2(5, 4), hft::HFFLOAT2(0, -1), 3);
	}
	if (GetAsyncKeyState('Y') & 0x0001)
	{
		SetSlideData(hft::HFFLOAT2(4, 4), hft::HFFLOAT2(0, 1), 3);
	}


	Slide();
	Debug_TilePaintColor_FromTile(7, tileObjects);
}
