#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>

#include "../../../06-GameObject/99-CameraObject/01-Camera2D/CameraObject2D.h"
#include "../../../06-GameObject/99-CameraObject/02-Camera3D/CameraObject3D.h"
#include "../../../06-GameObject/98-LightObject/LightObject.h"



class BaseScene
{
protected:
	CameraObject2D camera2D;
	CameraObject3D camera3D;
	LightObject lightObject;

public:
	BaseScene() {}
	virtual ~BaseScene() {}

	virtual void Init() = 0;
	virtual void UnInit() = 0;
};