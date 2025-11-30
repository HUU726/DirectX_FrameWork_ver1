#pragma once

#include "../../GameObject.h"

#include "../../../07-Component/04-Camera/02-Camera3D/Camera3D.h"


class CameraObject3D : public GameObject
{
private:
	Camera3D* p_comp_camera;
	Transform* p_standTransform;

public:
	CameraObject3D();
	~CameraObject3D();
	hft::HFFLOAT3 GetForward() { return p_comp_camera->GetForward(); }
	hft::HFFLOAT3 GetRight() { return p_comp_camera->GetRight(); }
	hft::HFFLOAT3 GetUp() { return p_comp_camera->GetUp(); }

	void SetStandPos(hft::HFFLOAT3 _pos) { p_transform->position = { _pos.x,_pos.y,_pos.z }; }
	void SetTransform(Transform* _c_p_transform) { p_standTransform = _c_p_transform; }


	void Init() override;
	void Update() override;
};

