#pragma once
#include "../../GameObject.h"
#include "../../../07-Component/04-Camera/01-Camera2D/Camera2D.h"

class CameraObject2D : public GameObject
{
private:
	Camera2D* p_comp_camera;

public:
	CameraObject2D();
	~CameraObject2D();
	void Init() override;
	void Update() override;
	void Draw() override;
};

