#pragma once

#include "../GameObject.h"


class CameraObject : public GameObject
{
private:
	

public:
	CameraObject();
	~CameraObject();
	void Init() override;
	void Update() override;
};

