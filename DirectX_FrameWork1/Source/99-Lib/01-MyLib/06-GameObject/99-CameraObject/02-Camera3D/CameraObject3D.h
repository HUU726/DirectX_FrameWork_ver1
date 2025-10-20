#pragma once

#include "../../GameObject.h"


class CameraObject3D : public GameObject
{
private:
	

public:
	CameraObject3D();
	~CameraObject3D();
	void Init() override;
	void Update() override;
	void Draw() override;
};

