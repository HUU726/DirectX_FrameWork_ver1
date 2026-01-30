#include "BaseMap.h"

#include "../../01-GamaeObject/01-TrackObject/00-TrackObject/TrackObject.h"
#include "../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#define MAP_CENTER_POSX (0)
#define MAP_CENTER_POSY (0)
#define MAP_SIZE (800.0f)
#define BASE_TILE_NUM (5.f)


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

	for (auto& data : slideDatas)
	{
		SlideTileObject(data);
		SlideTrackObject(data);
		if (data.changeFlg)
		{
			data.changeFlg = false;
			if (data.power < 1)
				data.power = 0;
		}

		if (data.cntFlame > powerDownFlame)
		{
			data.power *= powerDownRatio;
			data.cntFlame = 0;
		}
		else
		{
			data.cntFlame++;
		}
	}

	//ズレる力が０になったらパイプラインから除外
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
	for (const auto& obj : onMapTileObjects)
	{
		if (_data.moveVec.x)
		{
			if (obj->GetLineIndex().y == _data.anchorPos.y)
				_data.tiles.push_back(obj);
		}
		else if (_data.moveVec.y)
		{
			if (obj->GetLineIndex().x == _data.anchorPos.x)
				_data.tiles.push_back(obj);
		}
	}
}

void BaseMap::SlideTileObject(SlideData& _data)
{

	for (auto obj : _data.tiles)
	{
		Transform* p_trf = obj->GetTransformPtr();
		hft::HFFLOAT2 moveVec = { _data.moveVec.x,_data.moveVec.y * -1 };
		float posZ = p_trf->position.z;
		p_trf->position += moveVec * _data.power;

		float tileScaleHalf = tileScale / 2.0f;

		if (p_trf->position.x > rightBottomPos.x + tileScale || p_trf->position.x < leftTopPos.x - tileScale)
		{
			_data.changeFlg = true;
			_data.indexToChangeFlg = true;
		}
		else if (!_data.indexFlg &&
			(p_trf->position.x > rightBottomPos.x + tileScaleHalf || p_trf->position.x < leftTopPos.x - tileScaleHalf))
		{
			_data.indexFlg = true;
		}

		if (p_trf->position.y > leftTopPos.y + tileScale || p_trf->position.y < rightBottomPos.y - tileScale)
		{
			_data.changeFlg = true;
			_data.indexToChangeFlg = true;
		}
		else if (!_data.indexFlg &&
			(p_trf->position.y > leftTopPos.y + tileScaleHalf || p_trf->position.y < rightBottomPos.y - tileScaleHalf))
		{
			_data.indexFlg = true;
		}

		p_trf->position.z = posZ;
	}

	if ((_data.indexFlg && _data.indexToChangeFlg) || _data.changeFlg)
	{
		for (auto obj : _data.tiles)
		{
			hft::HFFLOAT2 index = obj->GetLineIndex();
			if (_data.changeFlg)
			{
				SetLineIndexToPosOfTile(index, *obj);
				if (!_data.objects.size())
					_data.indexFlg = false;
			}
			else
			{
				index += _data.moveVec;
				obj->SetLineIndex(index);
				if (!_data.objects.size())
					_data.indexToChangeFlg = false;
			}
		}
	}

}

void BaseMap::SearchOnLineObjects(SlideData& _data)
{

	for (const auto& obj : onMapTrackObjects)
	{
		if (_data.moveVec.x)
		{
			if (obj->GetLineIndex().y == _data.anchorPos.y)
				_data.objects.push_back(obj);
		}
		else if (_data.moveVec.y)
		{
			if (obj->GetLineIndex().x == _data.anchorPos.x)
				_data.objects.push_back(obj);
		}
	}
}

void BaseMap::SlideTrackObject(SlideData& _data)
{
	for (auto obj : _data.objects)
	{
		Transform* p_trf = obj->GetTransformPtr();
		hft::HFFLOAT2 moveVec = { _data.moveVec.x,_data.moveVec.y * -1 };
		p_trf->position += moveVec * _data.power;
	}

	if ((_data.indexFlg && _data.indexToChangeFlg) || _data.changeFlg)
	{
		for (auto obj : _data.objects)
		{
			hft::HFFLOAT2 index = obj->GetLineIndex();
			if (_data.changeFlg)
			{
				//SetLineIndexToPosOfTile(index, *obj);
				_data.indexFlg = false;
			}
			else
			{
				index += _data.moveVec;
				obj->SetLineIndex(index);
				if ((index.x == 0 || index.x == width - 1) ||
					(index.y == 0 || index.y == height - 1))
					SetLineIndexToPosOfTrackObject(_data.moveVec, index, *obj);
				_data.indexToChangeFlg = false;
			}

		}
	}
}

void BaseMap::SetLineIndexToPosOfTile(hft::HFFLOAT2& _index, TrackObject& _obj)
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
	pos.x = leftTopPos.x + _index.x * tileScale;
	pos.y = leftTopPos.y - _index.y * tileScale;
}

void BaseMap::SetLineIndexToPosOfTrackObject(const hft::HFFLOAT2& _moveVec, hft::HFFLOAT2& _index, TrackObject& _obj)
{
	if (_index.x < 1)
		_index.x = width - 2;
	else if (_index.x >= width - 1)
		_index.x = 1;

	if (_index.y < 1)
		_index.y = height - 2;
	else if (_index.y >= height - 1)
		_index.y = 1;

	_obj.SetLineIndex(_index);
	float tileScaleHalf = tileScale / 2.f;
	hft::HFFLOAT4& pos = _obj.GetTransformPtr()->position;
	pos.x = leftTopPos.x + _index.x * tileScale + (tileScaleHalf * _moveVec.x * -1);
	pos.y = leftTopPos.y - _index.y * tileScale + (tileScaleHalf * _moveVec.y);
}


void BaseMap::InitBiteEnemyVec(const std::vector<int>& _vec)
{
	biteEnemyVecs.insert(biteEnemyVecs.end(), _vec.begin(), _vec.end());
}

void BaseMap::InitGunEnemyVec(const std::vector<int>& _vec)
{
	gunEnemyVecs.insert(gunEnemyVecs.end(), _vec.begin(), _vec.end());
}

#include "../../../02-App/Application.h"
#include "../../../02-App/HF_Window.h"
void BaseMap::CreateTiles()
{
	scaleRaito = BASE_TILE_NUM / float(width);
	tileScale = MAP_SIZE / float(width);
	
	//ズラした時の隙間防止
	width += 2;
	height += 2;
	
	float tileScaleHalf = tileScale / 2.f;
	leftTopPos.x = MAP_CENTER_POSX - (width / 2.0f * tileScale) + tileScaleHalf;	//左端座標
	leftTopPos.y = MAP_CENTER_POSY + (height / 2.0f * tileScale) - tileScaleHalf;	//上端座標
	rightBottomPos.x = leftTopPos.x + ((width - 1) * tileScale);					//右端座標
	rightBottomPos.y = leftTopPos.y - ((height - 1) * tileScale);					//下端座標

	for (int y = 0; y < height; y++)
	{
		float posY = leftTopPos.y - (tileScale * y);
		for (int x = 0; x < width; x++)
		{
			auto tileObject = new	TrackObject;
			auto renderer = tileObject->GetComponent<SpriteRenderer>();
			renderer->LoadTexture("Assets/01-Texture/01-Map/Tile.png");
			auto p_trf = tileObject->GetTransformPtr();
			p_trf->scale = { tileScale,tileScale };

			float posX = leftTopPos.x + (tileScale * x);
			p_trf->position = { posX,posY,99 };
			tileObject->SetLineIndex(hft::HFFLOAT2(x, y));
			onMapTileObjects.push_back(tileObject);
		}
	}

	//背景読み込み
	{
		HF_Window* p_window = Application::GetInstance().GetWindowPtr();
		float width = p_window->GetWidth();
		float height = p_window->GetHeight();
		BGImg = new GameObject2D;
		auto renderer = BGImg->GetComponent<SpriteRenderer>();
		renderer->LoadTexture("Assets/01-Texture/01-Map/BGImg800.png");
		auto p_trf = BGImg->GetTransformPtr();
		p_trf->position.z = -20;
		p_trf->scale = { width,height,1 };
	}
}

#include "../../01-GamaeObject/01-TrackObject/04-Player/PlayerObject.h"
#include "../../01-GamaeObject/01-TrackObject/04_Enemy/BiteEnemy.h"
#include "../../01-GamaeObject/01-TrackObject/04_Enemy/GunEnemy.h"
#include "../../01-GamaeObject/01-TrackObject/04_Enemy/BombEnemy.h"
#include "../../01-GamaeObject/01-TrackObject/03_ConnectObject/ConnectObject.h"
#include "../../01-GamaeObject/01-TrackObject/02_ThornObject/ThormObject.h"
#include "../../../04-Input/Input.h"
void BaseMap::CreateObjects()
{
	auto biteVec = biteEnemyVecs.begin();
	auto gunVec = gunEnemyVecs.begin();

	int size = mapDataArray.size();
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{

			TrackObject* p_trackObj = nullptr;

			int& data = mapDataArray[y][x];
			float indexX = x + 1;
			float indexY = y + 1;
			switch (data)
			{
			case PLAYER:
				{
					PlayerObject* p_obj = new PlayerObject;
					p_obj->Init(this, &Input::GetInstance());
					p_obj->GetTransformPtr()->position.z = -1;
					p_trackObj = p_obj;
				}
				break;
			case BITE_ENEMY:
				{
					biteVec += 1;
					BiteEnemy* p_obj = new BiteEnemy;
					p_obj->Init(*biteVec);
					p_obj->GetTransformPtr()->position.z = -2;
					p_trackObj = p_obj;
				}
				break;
			case GUN_ENEMY:
				{
					++gunVec;
					GunEnemy* p_obj = new GunEnemy;
					p_obj->Init(this, *gunVec);
					p_obj->GetTransformPtr()->position.z = -3;
					p_trackObj = p_obj;
				}
				break;
			case BOMB_ENEMY:
				{
					BombEnemy* p_obj = new BombEnemy;
					p_obj->Init();
					p_obj->GetTransformPtr()->position.z = -4;
					p_trackObj = p_obj;
				}
				break;
			case CONNECT_OBJ:
				{
					ConnectObject* p_obj = new ConnectObject;
					p_obj->Init(this);
					p_obj->GetTransformPtr()->position.z = -5;
					p_trackObj = p_obj;
				}
				break;
			case THORM_OBJ:
				{
					ThormObject* p_obj = new ThormObject;
					p_obj->Init();
					p_obj->GetTransformPtr()->position.z = -6;
					p_trackObj = p_obj;
				}
				break;
			default:
				break;
			}

			if (p_trackObj == nullptr)
				continue;

			p_trackObj->SetLineIndex({ indexX,indexY });
			Transform* p_trf = p_trackObj->GetTransformPtr();
			p_trf->position.x = leftTopPos.x + (tileScale * indexX);
			p_trf->position.y = leftTopPos.y - (tileScale * indexY);
			p_trf->scale = p_trf->scale * scaleRaito;
			onMapTrackObjects.push_back(p_trackObj);

		}

	}
}

BaseMap::BaseMap()
{
	p_transform->position.x = MAP_CENTER_POSX;
	p_transform->position.y = MAP_CENTER_POSY;

	powerDownFlame = 35;
	powerDownRatio = 0.8f;

	biteEnemyVecs.emplace_back(0);
	gunEnemyVecs.emplace_back(0);
}

BaseMap::~BaseMap()
{

	for (auto& p_tile : onMapTileObjects)
		delete p_tile;

	for (auto& p_obj : onMapTrackObjects)
		delete p_obj;

	delete BGImg;
}


#include "../../../99-Lib/01-MyLib/06-GameObject/999-GameObjectManager/GameObjectManager.h"
void BaseMap::SetSlideData(const hft::HFFLOAT2& _anchorPos, const hft::HFFLOAT2& _moveVec, const float& _power)
{
	//ズレが存在するか確認
	{
		if (slideDatas.size() <= 0)
		{
			SlideData data{ _anchorPos,_moveVec,_power };
			SearchOnLineTiles(data);
			SearchOnLineObjects(data);
			slideDatas.push_back(data);
			return;
		}
	}

	//すでに動いているか確認
	{
		for (auto data : slideDatas)
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
		hft::HFFLOAT2 curMoveVec = slideDatas.at(0).moveVec;
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

				for (auto data : slideDatas)
				{
					float ancPos = (data.anchorPos.x * moveVecFlg.x) + (data.anchorPos.y * moveVecFlg.y);
					if (ancPos != i)
						continue;

					if (_power < data.power)
						return;

					auto it = std::find(slideDatas.begin(), slideDatas.end(), data);
					if (it != slideDatas.end())
					{
						//ここで列を綺麗に整える
						for (auto obj : it->tiles)
						{
							hft::HFFLOAT2 index = obj->GetLineIndex();
							//index -= data.moveVec;
							SetLineIndexToPosOfTile(index, *obj);
						}
						for (auto obj : it->objects)
						{
							hft::HFFLOAT2 index = obj->GetLineIndex();
							//index -= data.moveVec;
							SetLineIndexToPosOfTile(index, *obj);
						}
						slideDatas.erase(it);
					}

				}
			}
		}
	}

	SlideData data{ _anchorPos,_moveVec,_power };
	SearchOnLineTiles(data);
	SearchOnLineObjects(data);
	slideDatas.push_back(data);
}

bool BaseMap::IsValidTarget(const hft::HFFLOAT2& _index)
{
	// ---------------------------------------------------
	// 範囲チェック
	// ---------------------------------------------------

	// 「1未満」または「width-2 より大きい」ならNG
	if (_index.x < 1 || _index.x >= width - 1) return false;
	if (_index.y < 1 || _index.y >= height - 1) return false;

	// ---------------------------------------------------
	// スライド中チェック
	// ---------------------------------------------------
	for (const auto& data : slideDatas)
	{
		if (data.moveVec.x != 0.0f)
		{
			if (static_cast<int>(data.anchorPos.y) == static_cast<int>(_index.y))
			{
				std::cout << "can't select : reason...target is sliding now." << std::endl;
				return false;
			}
		}
		else if (data.moveVec.y != 0.0f)
		{
			if (static_cast<int>(data.anchorPos.x) == static_cast<int>(_index.x))
			{
				std::cout << "can't select : reason...target is sliding now." << std::endl;
				return false;
			}
		}
	}

	hft::HFFLOAT2 objline;
	for (const auto& obj : onMapTrackObjects)
	{
		objline = obj->GetLineIndex();
		if (_index == objline && obj->GetTag() != "TuningFork" && obj->GetTag() != "Player")
		{
			std::cout << "can't select : reason...Tag: " << obj->GetTag() << std::endl;
			return false;
		}
	}

	return true;
}

void BaseMap::Init()
{
	CreateMap();
	CreateTiles();
	CreateObjects();
}

#include "../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../01-GamaeObject/01-TrackObject/01-TestObject/TestObject.h"

void BaseMap::Init(const int& _width, const int& _height)
{
	scaleRaito = BASE_TILE_NUM / _width;
	tileScale = MAP_SIZE / float(_width);
	float tileScaleHalf = tileScale / 2.f;
	width = _width + 2;
	height = _height + 2;

	leftTopPos.x = MAP_CENTER_POSX - (width / 2.0f * tileScale) + tileScaleHalf;
	leftTopPos.y = MAP_CENTER_POSY + (height / 2.0f * tileScale) - tileScaleHalf;
	rightBottomPos.x = leftTopPos.x + ((width - 1) * tileScale);
	rightBottomPos.y = leftTopPos.y - ((height - 1) * tileScale);

	for (int y = 0; y < height; y++)
	{
		float posY = leftTopPos.y - (tileScale * y);
		for (int x = 0; x < width; x++)
		{
			auto tileObject = new	TrackObject;
			auto renderer = tileObject->GetComponent<SpriteRenderer>();
			renderer->LoadTexture("Assets/01-Texture/01-Map/Tile.png");
			tileObject->GetTransformPtr()->scale = { tileScale,tileScale };

			float posX = leftTopPos.x + (tileScale * x);
			tileObject->GetTransformPtr()->position = { posX,posY,99 };
			tileObject->SetLineIndex(hft::HFFLOAT2(x, y));
			onMapTileObjects.push_back(tileObject);
		}
	}

	{
		PlayerObject* p_obj = new PlayerObject;
		p_obj->SetLineIndex({ 3,3 });
		p_obj->Init(this, &Input::GetInstance());
		Transform* p_trf = p_obj->GetTransformPtr();
		p_trf->position.x = leftTopPos.x + (tileScale * 3);
		p_trf->position.y = leftTopPos.y - (tileScale * 3);
		p_trf->position.z = -1;
		onMapTrackObjects.push_back(p_obj);
	}

	{
		BombEnemy* bom = new BombEnemy;
		bom->Init();
		Transform* p_trf = bom->GetTransformPtr();
		p_trf->position.x = leftTopPos.x + (tileScale * 4);
		p_trf->position.y = leftTopPos.y - (tileScale * 4);
		p_trf->position.z = -1;
		onMapTrackObjects.push_back(bom);
	}

	for (auto& obj : onMapTrackObjects)
	{
		Transform* p_trf = obj->GetTransformPtr();
		p_trf->scale = p_trf->scale * scaleRaito;
	}
}

#include "../../../99-Lib/01-MyLib/08-Scene/02-SceneManager/SceneManager.h"
#include "../../../99-Lib/01-MyLib/08-Scene/01-Scenes/GameScene.h"
void BaseMap::Update()
{
	Slide();

	for (const auto& obj : onMapTrackObjects)
	{
		std::cout << obj->GetTransform().position.z << std::endl;
	}
}
