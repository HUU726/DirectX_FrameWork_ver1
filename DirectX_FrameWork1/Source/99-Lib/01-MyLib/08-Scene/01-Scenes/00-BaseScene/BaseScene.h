#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>
#include "../../../06-GameObject/01-2DGameObject/GameObject2D.h"
#include "../../../06-GameObject/02-3DGameObject/GameObject3D.h"

#include "../../../06-GameObject/99-CameraObject/01-Camera2D/CameraObject2D.h"
#include "../../../06-GameObject/99-CameraObject/02-Camera3D/CameraObject3D.h"

#include "../../../06-GameObject/98-LightObject/LightObject.h"



class BaseScene
{
protected:
	std::unique_ptr<BaseScene> nextScene;

public:
	BaseScene() : nextScene(nullptr) {}
	virtual ~BaseScene() {}

	std::unique_ptr<BaseScene> GetNextScene()
	{
		return std::move(nextScene);
	}

	virtual void Init() = 0;
	virtual void UnInit() = 0;
};