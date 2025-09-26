#pragma once


#include "../../00-Component/Component.h"
#include <vector>
#include <DirectXMath.h>


class IF_Camera : public Component
{
protected:
	float nearClip;	//最近クリップ距離
	float farClip;	//最遠クリップ距離
	int priority;	//描画優先度(昇順)

	DirectX::XMFLOAT3* p_targetPos;

	enum VIEW_ELEMENT
	{
		CAMERA_POS = 0,
		TARGET_POS,
		UP_DIRECT,
		ALL_ELEMENT,
	};

	DirectX::XMFLOAT3 forward;
	DirectX::XMFLOAT3 right;
	DirectX::XMFLOAT3 up;

	DirectX::XMMATRIX matrixView;
	DirectX::XMMATRIX matrixProj;

	virtual std::vector<DirectX::XMVECTOR> DeriveTargetToForward() = 0;
	virtual std::vector<DirectX::XMVECTOR> DeriveForwardToTarget() = 0;
	void UpdateViewMatrix();

public:
	/*** ゲッター ***/
	DirectX::XMMATRIX GetMatrixView() { return matrixView; }
	DirectX::XMMATRIX GetMatrixProj() { return matrixProj; }
	DirectX::XMFLOAT3 GetForward() { return forward; }
	DirectX::XMFLOAT3 GetRight() { return right; }
	DirectX::XMFLOAT3 GetUp() { return up; }

	/*** セッター ***/
	void SetTargetPos(DirectX::XMFLOAT3* _p_pos) { p_targetPos = _p_pos; }
};

