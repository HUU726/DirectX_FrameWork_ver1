#include "Camera.h"

#include "../../06-GameObject/GameObject.h"
#include "../01-Transform/Transform.h"

void Camera::UpdateViewMatrix()
{
	Transform* transform = GetGameObject()->GetTransformPtr();
	auto pos = transform->position;
	auto rot = transform->rotation;
	DirectX::XMVECTOR eye = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f);
	DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	at = DirectX::XMVector3TransformCoord(at, rotMat);
	at = DirectX::XMVectorAdd(eye, at);
	up = DirectX::XMVector3TransformCoord(up, rotMat);
	matrixView = DirectX::XMMatrixLookAtLH(eye, at, up);
}

Camera::Camera()
{
	fov = 60.0f;
	aspectRatio = 16.0f / 9.0f;
	nearClip = 0.1f;
	farClip = 1000.0f;
}

Camera::Camera(float _fov, float _aspectRatio, float _nearClip, float _farClip)
{
	fov = _fov;
	aspectRatio = _aspectRatio;
	nearClip = _nearClip;
	farClip = _farClip;
}

Camera::~Camera()
{}

void Camera::Init()
{
}

void Camera::Update()
{
	UpdateViewMatrix();
}
