#pragma once


#include "../../00-Component/Component.h"
#include "../../../998-FH_Types/HF_FLOAT.h"
#include <vector>


class IF_Camera : public Component
{
protected:
	float nearClip;	//最近クリップ距離
	float farClip;	//最遠クリップ距離
	int priority;	//描画優先度(昇順)

	hft::HFFLOAT3* p_targetPos;

	enum VIEW_ELEMENT
	{
		CAMERA_POS = 0,
		TARGET_POS,
		UP_DIRECT,
		ALL_ELEMENT,
	};

	hft::HFFLOAT3 forward;
	hft::HFFLOAT3 right;
	hft::HFFLOAT3 up;

	DirectX::XMMATRIX matrixView;
	DirectX::XMMATRIX matrixProj;

	virtual std::vector<DirectX::XMVECTOR> DeriveTargetToForward() = 0;
	virtual std::vector<DirectX::XMVECTOR> DeriveForwardToTarget() = 0;
	void UpdateViewMatrix();

public:
	/*** ゲッター ***/
	DirectX::XMMATRIX GetMatrixView() { return matrixView; }
	DirectX::XMMATRIX GetMatrixProj() { return matrixProj; }
	hft::HFFLOAT3 GetForward() { return forward; }
	hft::HFFLOAT3 GetRight() { return right; }
	hft::HFFLOAT3 GetUp() { return up; }

	/*** セッター ***/
	void SetTargetPos(hft::HFFLOAT3* _p_pos) { p_targetPos = _p_pos; }
};

