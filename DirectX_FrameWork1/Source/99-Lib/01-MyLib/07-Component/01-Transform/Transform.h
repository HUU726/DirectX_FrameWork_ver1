#pragma once

#include "../00-Component/Component.h"
#include "../../998-FH_Types/HF_FLOAT.h"


struct Transform : public Component
{
	hft::HFFLOAT4 position = { 0.f,0.f,0.f,0.f };
	hft::HFFLOAT3 rotation = { 0.f,0.f,0.f };
	hft::HFFLOAT3 scale = { 0.f,0.f,0.f };
	Transform() {}
	Transform(const Transform& _transform) : position(_transform.position), rotation(_transform.rotation), scale(_transform.scale) {}
	void Init() override {}
	void Update() override {}
};