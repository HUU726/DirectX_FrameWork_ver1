#pragma once

#include "../02-3DGameObject/GameObject3D.h"

enum class LIGHT_TYPE
{
	DIRECT=0,
	POINT,
	SPOT,
	AMBI,
};

class Light;

class LightObject : public GameObject3D
{
protected:
	LIGHT_TYPE type;		//ライトの種類
	Light* p_comp_light;	//ライトコンポネントポインタ

public:
	LightObject();

	/**
	* @brief	ライトの種類をセット
	* @param	LIGHT_TYPE	_type	ライトの種類　※列挙型
	*/
	void SetLightType(LIGHT_TYPE _type);
	void Init() override;
	void Update() override;

};

