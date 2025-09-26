#pragma once


#include "../00-Component/Component.h"
#include "../01-Transform/Transform.h"
#include <DirectXMath.h>

class Camera : public Component
{
private:
	float fov;
	float aspectRatio;
	float nearClip;
	float farClip;

	DirectX::XMFLOAT3* p_targetPos;

	DirectX::XMFLOAT3 forward;
	DirectX::XMFLOAT3 right;
	DirectX::XMFLOAT3 up;
	
	DirectX::XMMATRIX matrixView;	//ビュー行列
	DirectX::XMMATRIX matrixProj;	//プロジェクション行列

	std::vector<DirectX::XMVECTOR> DeriveTargetToForward();
	std::vector<DirectX::XMVECTOR> DeriveForwardToTarget();
	void UpdateViewMatrix();

public:
	Camera();
	Camera(float _fov, float _aspectRatio, float _newarClip, float forClip);
	~Camera();

	/*** ゲッター ***/
	DirectX::XMMATRIX GetMatrixView() { return matrixView; }
	DirectX::XMFLOAT3 GetForward() { return forward; }
	DirectX::XMFLOAT3 GetRight() { return right; }
	DirectX::XMFLOAT3 GetUp() { return up; }

	/*** セッター ***/
	void SetTargetPos(DirectX::XMFLOAT3* _p_pos) { p_targetPos = _p_pos; }

	void Init() override;
	void Update() override;

};