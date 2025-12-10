#pragma once


#include "../../../99-Lib/01-MyLib/06-GameObject/GameObject.h"
#include "../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"
#include <vector>

class TrackObject;

class BaseMap : public GameObject
{
protected:
	int width;	//横幅
	int height;	//縦幅
	int* p_mapDataArray;	//マップのデータに次元配列

	hft::HFFLOAT2 anchorPos;	//ズラす基点
	hft::HFFLOAT2 moveVec;		//ズラす方向
	float power;				//ズラす力
	std::vector<TrackObject*> trackObjects;	//ズレ列に対応するオブジェクトのポインタ格納用

	void Slide();
	void TrackObjectUpdate();

public:
	BaseMap() : width(0), height(0), p_mapDataArray(nullptr), power(0) {}
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