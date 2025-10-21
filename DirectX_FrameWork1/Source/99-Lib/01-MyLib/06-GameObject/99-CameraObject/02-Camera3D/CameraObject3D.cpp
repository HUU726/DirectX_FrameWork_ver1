#include "CameraObject3D.h"

#include "../../../07-Component/04-Camera/02-Camera3D/Camera3D.h"


CameraObject3D::CameraObject3D()
{
	p_comp_camera = AddComponent<Camera3D>();
}

CameraObject3D::~CameraObject3D()
{
}

void CameraObject3D::Init()
{
}

void CameraObject3D::Update()
{
	p_comp_camera->Update();
}

void CameraObject3D::Draw()
{
}
