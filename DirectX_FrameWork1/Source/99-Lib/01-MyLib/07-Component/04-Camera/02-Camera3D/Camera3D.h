#pragma once


#include "../00-IF_Camera/IF_Camera.h"
#include "../../01-Transform/Transform.h"
#include <DirectXMath.h>




class Camera3D : public IF_Camera
{
private:
	float fov;
	float aspect;

	std::vector<DirectX::XMVECTOR> DeriveTargetToForward() override;
	std::vector<DirectX::XMVECTOR> DeriveForwardToTarget() override;

public:
	Camera3D();
	Camera3D(float _fov, float _aspectRatio, float _newarClip, float forClip);
	~Camera3D();


	void Init() override;
	void Update() override;
	void Action() override;

};