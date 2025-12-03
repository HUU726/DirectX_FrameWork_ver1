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
	LIGHT_TYPE type;
	Light* p_comp_light;

public:
	LightObject();
	void SetLightType(LIGHT_TYPE _type);
	void Init() override;
	void Update() override;

};

