#pragma once


#include "../../../99-Lib/01-MyLib/06-GameObject/GameObject.h"
#include "../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"
#include <vector>

class TrackObject;

struct SlideData
{
	hft::HFFLOAT2 anchorPos;
	hft::HFFLOAT2 moveVec;
	float power;
	std::vector<TrackObject*> trackObjects;
};

class BaseMap : public GameObject
{
protected:
	int width;	//横幅
	int height;	//縦幅
	int* p_mapDataArray;	//マップのデータに次元配列

	std::vector<SlideData> slideDatas;	//ズラす時に使うデータ
	std::vector<TrackObject*> onMapTrackObjects;	//マップに存在するTrackObjectのポインタ

	/**
	* @brief	ズラす処理
	*/
	void Slide();
	/**
	* @brief	ライン上のオブジェクトを取得する処理
	*/
	void SearchOnLineObjects(SlideData& _data);
	/**
	* @brief	追従オブジェクトの座標をズラす
	*/
	void SlideTrackObject();

public:
	BaseMap() {}
	virtual ~BaseMap() {}

	/**
	* @brief	マップをズラす時のプレイヤーからもらうデータ
	* @param	const hft::HFFLOAT2&	基点
	* @param	const hft::HFFLOAT2&	方向
	* @param	const float&			力
	*/
	void SetSlideData(const hft::HFFLOAT2& _anchorPos, const hft::HFFLOAT2& _moveVec, const float& _power);

	/**
	* @brief	マップのサイズを初期化
	* @param	const int&	_width	マップ横幅
	* @height	const int&	_height	マップ縦幅
	*/
	void Init(const int& _width, const int& _height);

};