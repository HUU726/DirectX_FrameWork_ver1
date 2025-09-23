#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>


#include "Camera.h"


class BaseScene
{
protected:
	std::unique_ptr<BaseScene> nextScene;

	Camera camera;

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