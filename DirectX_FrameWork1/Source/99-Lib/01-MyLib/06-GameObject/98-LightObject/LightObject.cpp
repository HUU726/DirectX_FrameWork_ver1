#include "LightObject.h"

#include "../../07-Component/05-Light/Light.h"

LightObject::LightObject()
{
	p_comp_light = AddComponent<Light>();
}

void LightObject::SetLightType(LIGHT_TYPE _type)
{
}

void LightObject::Init()
{
}

void LightObject::Update()
{
	p_comp_light->Update();
}
