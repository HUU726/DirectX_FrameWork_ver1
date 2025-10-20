#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>
#include "../../../06-GameObject/01-2DGameObject/GameObject2D.h"
#include "../../../06-GameObject/"

#include "../../../06-GameObject/99-CameraObject/01-Camera2D/CameraObject2D.h"
#include "../../../06-GameObject/99-CameraObject/02-Camera3D/CameraObject3D.h"



class BaseScene
{
protected:
	std::unique_ptr<BaseScene> nextScene;

public:
	BaseScene() : nextScene(nullptr) {}
	~BaseScene() = default;

	std::unique_ptr<BaseScene> GetNextScene()
	{
		return std::move(nextScene);
	}

	virtual void Init() = 0;
	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void UnInit() = 0;
};