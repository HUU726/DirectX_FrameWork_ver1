#pragma once
#include "../../GameObject.h"

class CameraObject2D : public GameObject
{
private:


public:
	CameraObject2D();
	~CameraObject2D();
	void Init() override;
	void Update() override;
	void Draw() override;
};

