#include "Camera2D.h"
#include "../../../06-GameObject/GameObject.h"


std::vector<DirectX::XMVECTOR> Camera2D::DeriveTargetToForward()
{
	std::vector<DirectX::XMVECTOR> ansVector;
	ansVector.resize(ALL_ELEMENT);

	Transform transform = GetGameObject()->GetTransform();
	auto rot = transform.rotation;
	auto defaultUp = DirectX::XMVECTOR{ 0.f,1.f,0.f,0.f };
	auto matrixRot = DirectX::XMMatrixRotationRollPitchYaw(0.f,0.f, rot.z);

	auto pos = p_targetPos;
	auto cameraPos = DirectX::XMVectorSet(pos->x, pos->y, pos->z - 1.f, 0.f);
	auto targetPos = DirectX::XMVectorSet(pos->x, pos->y, pos->z, 0.f);

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

std::vector<DirectX::XMVECTOR> Camera2D::DeriveForwardToTarget()
{
	std::vector<DirectX::XMVECTOR> ansVector;
	ansVector.resize(ALL_ELEMENT);

	Transform transform = GetGameObject()->GetTransform();
	auto pos = transform.position;
	auto rot = transform.rotation;

	auto defaultUp = DirectX::XMVECTOR{ 0.f,1.f,0.f,0.f };
	auto matrixRot = DirectX::XMMatrixRotationRollPitchYaw(0.f, 0.f, rot.z);

	auto cameraPos = DirectX::XMVectorSet(pos.x,pos.y,pos.z,0.f);
	auto targetPos = DirectX::XMVectorSet(pos.x,pos.y,pos.z+1,0.f);

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


Camera2D::Camera2D()
{
	width = 800.f;
	height = 600.f;
	nearClip = 0.1f;
	farClip = 1000.0f;
	p_targetPos = nullptr;
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
	p_targetPos = nullptr;
	forward = { 0.f,0.f,1.f };
	right = { 1.f,0.f,0.f };
	up = { 0.f,1.f,0.f };
}

Camera2D::~Camera2D()
{
}

void Camera2D::Init()
{
	matrixProj = DirectX::XMMatrixOrthographicLH(width, height, nearClip, farClip);
	UpdateViewMatrix();
}

void Camera2D::Update()
{
	UpdateViewMatrix();
}
