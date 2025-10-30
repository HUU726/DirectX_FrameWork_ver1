#include "LightObject.h"

#include "../../07-Component/05-Light/Light.h"
#include "../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"

LightObject::LightObject()
{

	p_comp_light = AddComponent<Light>();
	AddComponent<MeshRenderer>()->SetShape("light");
	Transform* p_trf = GetTransformPtr();
	p_trf->position = { -700.f,0.f,0.f };
	p_trf->rotation = { 0,0,0 };	//30,-40,0
	p_trf->scale = { 200,200,80 };


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
