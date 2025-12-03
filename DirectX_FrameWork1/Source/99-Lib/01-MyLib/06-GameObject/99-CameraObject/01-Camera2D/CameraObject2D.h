#pragma once
#include "../../GameObject.h"

class Camera2D;

class CameraObject2D : public GameObject
{
private:
	Camera2D* p_comp_camera;

public:
	CameraObject2D();
	~CameraObject2D();
	hft::HFFLOAT3 GetForward() const;
	hft::HFFLOAT3 GetRight() const;
	hft::HFFLOAT3 GetUp() const;
	void Init() override;
	void Update() override;
	void Draw() override;
};

