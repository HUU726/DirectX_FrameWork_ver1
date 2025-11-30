#pragma once


#include "../../06-GameObject/GameObject.h"
#include "../../06-GameObject/99-CameraObject/02-Camera3D/CameraObject3D.h"

class TestPlayer : public GameObject
{
private:
	Transform* p_cameraPos;
	CameraObject3D* p_camera3D;

public:
	
	void SetCameraObject3D(CameraObject3D* _p_cameraObject3D) { p_camera3D = _p_cameraObject3D; }

	void Init() override;
	void Update() override;

};