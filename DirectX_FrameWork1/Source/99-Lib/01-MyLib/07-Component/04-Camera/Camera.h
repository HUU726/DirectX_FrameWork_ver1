#pragma once


#include "../00-Component/Component.h"
#include <DirectXMath.h>

class Camera : public Component
{
private:
	float fov;
	float aspectRatio;
	float nearClip;
	float farClip;

	DirectX::XMVECTOR forward;
	DirectX::XMVECTOR right;
	DirectX::XMVECTOR up;
	
	DirectX::XMMATRIX matrixView;

	void UpdateViewMatrix();

public:
	Camera();
	Camera(float _fov, float _aspectRatio, float _newarClip, float forClip);
	~Camera();

	void Init() override;
	void Update() override;
	DirectX::XMMATRIX GetMatrixView() { return matrixView; }
	DirectX::XMVECTOR GetForward() {return forward; }
	DirectX::XMVECTOR GetRight() { return right; }
	DirectX::XMVECTOR GetUp() { return up; }

};