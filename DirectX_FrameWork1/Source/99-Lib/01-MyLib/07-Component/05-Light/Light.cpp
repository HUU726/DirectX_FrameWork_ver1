#include "Light.h"


#include "../../06-GameObject/GameObject.h"
#include "../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"


void Light::Init()
{
	data.enable = true;
	data.direction = { 1,1,1,0 };
	data.diffuse = { 1.5f,1.5f,1.5f,1.f };
	data.ambent = { 0.35f,0.35f,0.35f,1.f };
}

void Light::Update()
{
	Mesh3DRenderer& renderer = Mesh3DRenderer::GetInstance();
	hft::HFFLOAT3 rot = gameObject->GetTransform().rotation;
	DirectX::XMVECTOR eulerRad = DirectX::XMVectorSet(
		DirectX::XMConvertToRadians(rot.x),
		DirectX::XMConvertToRadians(rot.y),
		DirectX::XMConvertToRadians(rot.z),
		0.f
	);

	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYawFromVector(eulerRad);
	DirectX::XMVECTOR defaultDir = DirectX::XMVectorSet(0,0,1,0);
	DirectX::XMVECTOR lightDir = DirectX::XMVector3TransformNormal(defaultDir, rotMat);

	data.direction = DirectX::XMVector4Normalize(lightDir);
	renderer.SetLight(data);
}

LightData All_LightData::GetData()
{
    return allData;
}

void All_LightData::SetData(const LightData& _data)
{
    allData.diffuse = _data.diffuse;
}
