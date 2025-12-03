#pragma once

#include "../../GameObject.h"

class Camera3D;

class CameraObject3D : public GameObject
{
private:
	Camera3D* p_comp_camera;
	Transform* p_standTransform;

public:
	CameraObject3D();
	~CameraObject3D();
	hft::HFFLOAT3 GetForward() const;
	hft::HFFLOAT3 GetRight() const;
	hft::HFFLOAT3 GetUp() const;

	void SetStandPos(hft::HFFLOAT3 _pos) { p_transform->position = { _pos.x,_pos.y,_pos.z }; }
	void SetTransform(Transform* _c_p_transform) { p_standTransform = _c_p_transform; }


	void Init() override;
	void Update() override;
};

