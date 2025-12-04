#include "CameraObject3D.h"

#include "../../../07-Component/04-Camera/02-Camera3D/Camera3D.h"


CameraObject3D::CameraObject3D()
{
	p_comp_camera = AddComponent<Camera3D>();
}

CameraObject3D::~CameraObject3D()
{
}

hft::HFFLOAT3 CameraObject3D::GetForward() const
{
	return p_comp_camera->GetForward();
}
hft::HFFLOAT3 CameraObject3D::GetRight() const
{
	return p_comp_camera->GetRight();
}
hft::HFFLOAT3 CameraObject3D::GetUp() const
{
	return p_comp_camera->GetUp();
}


void CameraObject3D::SetStandPos(hft::HFFLOAT3 _pos)
{
	p_transform->position = { _pos.x,_pos.y,_pos.z };
}
void CameraObject3D::SetStandPos(Transform* _p_transform)
{
	p_standTransform = _p_transform;
}
void CameraObject3D::SetTarget(GameObject* _p_gameObject)
{
	p_comp_camera->SetTarget(_p_gameObject);
}



void CameraObject3D::Init()
{
}

/**
* @note		カメラが追跡する座標があれば毎フレームそのオブジェクトの座標の値で自身の座標を更新
*/
void CameraObject3D::Update()
{
	if (p_standTransform != nullptr)
	{
		*p_transform = *p_standTransform;
	}
	p_comp_camera->Update();
}
