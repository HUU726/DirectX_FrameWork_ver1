#pragma once
#include "../00-IF_Camera/IF_Camera.h"



class Camera2D : public IF_Camera
{
private:
	float width;
	float height;

	std::vector<DirectX::XMVECTOR> DeriveTargetToForward() override;
	std::vector<DirectX::XMVECTOR> DeriveForwardToTarget() override;

public:
	Camera2D();
	Camera2D(float _width, float _height, float _newarClip, float forClip);
	~Camera2D();

	void Init() override;
	void Update() override;
	void Action() override;

};

