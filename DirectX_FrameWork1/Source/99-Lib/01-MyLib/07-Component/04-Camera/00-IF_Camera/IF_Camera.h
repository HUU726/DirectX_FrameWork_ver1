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

	GameObject* p_target;	//カメラの見る先

	enum VIEW_ELEMENT
	{
		CAMERA_POS = 0,
		TARGET_POS,
		UP_DIRECT,
		ALL_ELEMENT,
	};

	hft::HFFLOAT3 forward;	//前ベクトル
	hft::HFFLOAT3 right;	//右ベクトル
	hft::HFFLOAT3 up;		//上ベクトル

	DirectX::XMMATRIX matrixView;	//View行列
	DirectX::XMMATRIX matrixProj;	//Projection行列

	virtual std::vector<DirectX::XMVECTOR> DeriveTargetToForward() = 0;
	virtual std::vector<DirectX::XMVECTOR> DeriveForwardToTarget() = 0;
	void UpdateViewMatrix();

public:
	/*** ゲッター ***/
	DirectX::XMMATRIX GetMatrixView() const { return matrixView; }
	DirectX::XMMATRIX GetMatrixProj() const { return matrixProj; }
	hft::HFFLOAT3 GetForward() const { return forward; }
	hft::HFFLOAT3 GetRight() const { return right; }
	hft::HFFLOAT3 GetUp() const { return up; }

	/*** セッター ***/
	void SetTarget(GameObject* _p_target) { p_target = _p_target; }


	void RemoveTarget() { p_target = nullptr; }

};

