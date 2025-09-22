#pragma once

#include "../00-Component/Component.h"
#include <DirectXMath.h>


struct Transform : public Component
{
	DirectX::XMFLOAT4 position = { 0.f,0.f,0.f,0.f };
	DirectX::XMFLOAT3 rotation = { 0.f,0.f,0.f };
	DirectX::XMFLOAT3 scale = { 0.f,0.f,0.f };
	Transform() {}
	Transform(const Transform& _transform) : position(_transform.position), rotation(_transform.rotation), scale(_transform.scale) {}
	void Init() override {}
	void Update() override {}
};