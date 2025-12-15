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
	std::vector<TrackObject*> trackObjects;
	int cntFlame;
	bool changeFlg;

	bool operator==(const SlideData& _data)
	{
		return (anchorPos == _data.anchorPos &&
			moveVec == _data.moveVec &&
			power == _data.power &&
			trackObjects == _data.trackObjects);
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
	std::vector<TrackObject*> tileObjects;

	std::vector<SlideData> slideDatas;	//ズラす時に使うデータ
	std::vector<TrackObject*> onMapTrackObjects;	//マップに存在するTrackObjectのポインタ

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

public:
	BaseMap();
	~BaseMap()
	{
		for (auto tile : tileObjects)
			delete tile;
	}

	/**
	* @brief	マップをズラす時のプレイヤーからもらうデータ
	* @param	const hft::HFFLOAT2&	基点
	* @param	const hft::HFFLOAT2&	方向
	* @param	const float&			力
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