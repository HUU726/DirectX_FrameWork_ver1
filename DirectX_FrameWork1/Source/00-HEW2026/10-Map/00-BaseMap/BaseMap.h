#pragma once


#include "../../../99-Lib/01-MyLib/06-GameObject/GameObject.h"
#include "../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"
#include <vector>

class TrackObject;



//ズラしに必要な情報
struct SlideData
{
	hft::HFFLOAT2 anchorPos;
	hft::HFFLOAT2 moveVec;
	float power;
	std::vector<TrackObject*> tiles;
	std::vector<TrackObject*> objects;
	int cntFlame;
	bool changeFlg;
	bool indexFlg;
	bool indexToChangeFlg = true;

	bool operator==(const SlideData& _data)
	{
		return (anchorPos == _data.anchorPos &&
			moveVec == _data.moveVec &&
			power == _data.power &&
			tiles == _data.tiles);
	}
};



class BaseMap : public GameObject
{
protected:
	int width;	//横幅
	int height;	//縦幅
	hft::HFFLOAT2 leftTopPos;
	hft::HFFLOAT2 rightBottomPos;

	std::vector<std::vector<hft::HFFLOAT2>> mapDataArray;	//マップのデータに次元配列
	std::vector<TrackObject*> tileObjects;			//マップに存在するタイルのポインタ
	std::vector<TrackObject*> onMapTrackObjects;	//マップに存在するオブジェのポインタ
	std::vector<SlideData> slideDatas;	//タイルをズラす時に使うデータ

	int powerDownFlame;
	float powerDownRatio;

	std::vector<GameObject*> covers;

	/**
	* @brief	ズラす処理
	*/
	void Slide();
	/**
	* @brief	ライン上のタイルオブジェクトを取得
	*/
	void SearchOnLineTiles(SlideData& _data);
	/**
	* @brief	ライン上のタイルオブジェクトをズラす
	*/
	void SlideTileObject(SlideData& _data);
	/**
	* @brief	ライン上のオブジェクトを取得する
	*/
	void SearchOnLineObjects(SlideData& _data);
	/**
	* @brief	追従オブジェクトの座標をズラす
	*/
	void SlideTrackObject(SlideData& _data);
	/**
	* @brief	行列番号からタイルの座標調節を行う
	*/
	void SetLineIndexToPosOfTile(hft::HFFLOAT2& _index, TrackObject& _obj);
	/**
	* @brief	行列番号からTrackObjectの座標調節を行う
	*/
	void SetLineIndexToPosOfTrackObject(const hft::HFFLOAT2& _moveVec, hft::HFFLOAT2& _index, TrackObject& _obj);

public:
	BaseMap();
	~BaseMap();

	/*** ゲッター ***/
	const hft::HFFLOAT2& GetLefTopPos() { return leftTopPos; }
	const hft::HFFLOAT2& GetRitBotPos() { return rightBottomPos; }

	/**
	* @brief	マップをズラす時のプレイヤーからもらうデータ
	* @param	const hft::HFFLOAT2&	_anchorPos	基点
	* @param	const hft::HFFLOAT2&	_moveVec	方向
	* @param	const float&			_power		力
	*/
	void SetSlideData(const hft::HFFLOAT2& _anchorPos, const hft::HFFLOAT2& _moveVec, const float& _power);

	void Init() override;
	/**
	* @brief	マップのサイズを初期化
	* @param	const int&	_width	マップ横幅
	* @height	const int&	_height	マップ縦幅
	*/
	void Init(const int& _width, const int& _height);

	void Update() override;

};