#pragma once


#include "../00-Component/Component.h"
#include <DirectXMath.h>

class Camera : public Component
{
private:
	float fov;				// 視野角
	float aspectRatio;		// アスペクト比
	float nearClip;			// ニアクリップ距離
	float farClip;			// ファークリップ距離
	DirectX::XMMATRIX matrixView; // ビュー行列

	public:
	void Init() override;
	void Update() override;
};

