#pragma once
#include "../GameObject.h"
#include "../../07-Component/05-Light/Light.h"

enum class LIGHT_TYPE
{
	DIRECT=0,
	POINT,
	SPOT,
	AMBI,
};

class LightObject : public GameObject
{
protected:
	LIGHT_TYPE type;
	Light* p_comp_light;

public:
	LightObject();
	void SetLightType(LIGHT_TYPE _type);
	void Init() override;
	void Update() override;

};

