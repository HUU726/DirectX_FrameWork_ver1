#include "CameraObject2D.h"

#include "../../../07-Component/04-Camera/01-Camera2D/Camera2D.h"

CameraObject2D::CameraObject2D()
{
	AddComponent<Camera2D>();
}

CameraObject2D::~CameraObject2D()
{
}

void CameraObject2D::Init()
{
}

void CameraObject2D::Update()
{
}
