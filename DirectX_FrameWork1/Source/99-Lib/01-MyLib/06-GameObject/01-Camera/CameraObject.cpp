#include "CameraObject.h"

#include "../../07-Component/04-Camera/Camera.h"


CameraObject::CameraObject()
{
	AddComponent<Camera>();
}

CameraObject::~CameraObject()
{
}

void CameraObject::Init()
{
}

void CameraObject::Update()
{
}
