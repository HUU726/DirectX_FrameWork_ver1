#include "Camera2D.h"

#include "../../../06-GameObject/GameObject.h"
#include "../../../02-Renderer/01-Sprite2DRenderer/Sprite2DRenderer.h"
#include "../../../../../02-App/FH_Window.h"

/**
* @brief	目標から前・上・右を割り出す
* @date		2025/09/20
*/
std::vector<DirectX::XMVECTOR> Camera2D::DeriveTargetToForward()
{
	std::vector<DirectX::XMVECTOR> ansVector;
	ansVector.resize(ALL_ELEMENT);

	hft::HFFLOAT3 rot = gameObject->GetTransform().rotation;
	float roll = DirectX::XMConvertToRadians(rot.z);
	auto defaultUp = DirectX::XMVECTOR{ 0.f,1.f,0.f,0.f };

	auto matrixRot = DirectX::XMMatrixRotationRollPitchYaw(0.f,0.f, roll);

	const hft::HFFLOAT3& pos = p_target->GetTransform().position;
	auto cameraPos = DirectX::XMVectorSet(pos.x, pos.y, pos.z - 1.f, 0.f);
	auto targetPos = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.f);

	auto forwardDirect = DirectX::XMVectorSet(0.f,0.f,1.f,0.f);

	auto upDirect = DirectX::XMVector3TransformNormal(defaultUp, matrixRot);
	upDirect = DirectX::XMVector3Normalize(upDirect);

	auto rightDirect = DirectX::XMVector3Cross(upDirect, forwardDirect);
	rightDirect = DirectX::XMVector3Normalize(rightDirect);

	DirectX::XMStoreFloat3(&forward, forwardDirect);
	DirectX::XMStoreFloat3(&up, upDirect);
	DirectX::XMStoreFloat3(&right, rightDirect);

	ansVector.at(CAMERA_POS) = cameraPos;
	ansVector.at(TARGET_POS) = targetPos;
	ansVector.at(UP_DIRECT) = upDirect;

	return ansVector;
}

/**
* @brief	向いている方向から目標を割り出す
* @date		2025/09/20
*/
std::vector<DirectX::XMVECTOR> Camera2D::DeriveForwardToTarget()
{
	std::vector<DirectX::XMVECTOR> ansVector;
	ansVector.resize(ALL_ELEMENT);

	Transform transform = gameObject->GetTransform();
	hft::HFFLOAT4 pos = transform.position;
	hft::HFFLOAT3 rot = transform.rotation;
	float roll = DirectX::XMConvertToRadians(rot.z);

	auto matrixRot = DirectX::XMMatrixRotationRollPitchYaw(0.f, 0.f, roll);

	auto cameraPos = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.f);
	auto targetPos = DirectX::XMVectorSet(pos.x, pos.y, pos.z + 1, 0.f);

	auto forwardDirect = DirectX::XMVectorSet(0.f,0.f,1.f,0.f);

	auto defaultUp = DirectX::XMVECTOR{ 0.f,1.f,0.f,0.f };
	auto upDirect = DirectX::XMVector3TransformNormal(defaultUp, matrixRot);
	upDirect = DirectX::XMVector3Normalize(upDirect);

	auto rightDirect = DirectX::XMVector3Cross(upDirect, forwardDirect);
	rightDirect = DirectX::XMVector3Normalize(rightDirect);
	
	DirectX::XMStoreFloat3(&forward, forwardDirect);
	DirectX::XMStoreFloat3(&up, upDirect);
	DirectX::XMStoreFloat3(&right, rightDirect);

	ansVector.at(CAMERA_POS) = cameraPos;
	ansVector.at(TARGET_POS) = targetPos;
	ansVector.at(UP_DIRECT) = upDirect;

	return ansVector;
}


Camera2D::Camera2D()
{
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	nearClip = 0.1f;
	farClip = 100.0f;
	p_target = nullptr;
	forward = { 0.f,0.f,1.f };
	right = { 1.f,0.f,0.f };
	up = { 0.f,1.f,0.f };
}

Camera2D::Camera2D(float _width, float _height, float _newarClip, float forClip)
{
	width = _width;
	height = _height;
	nearClip = _newarClip;
	farClip = forClip;
	p_target = nullptr;
	forward = { 0.f,0.f,1.f };
	right = { 1.f,0.f,0.f };
	up = { 0.f,1.f,0.f };
}

Camera2D::~Camera2D()
{
}

void Camera2D::Init()
{
	Sprite2DRenderer::GetInstance().SetCamera(this);
	matrixProj = DirectX::XMMatrixOrthographicLH(width, height, nearClip, farClip);
	UpdateViewMatrix();
}

void Camera2D::Update()
{
	UpdateViewMatrix();
}
