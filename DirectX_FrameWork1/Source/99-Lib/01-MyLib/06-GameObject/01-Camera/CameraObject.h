#pragma once
#include "../GameObject.h"


class CameraObject : public GameObject
{
private:
	float fov;				// 視野角
	float aspectRatio;		// アスペクト比
	float nearClip;			// ニアクリップ距離
	float farClip;			// ファークリップ距離
	DirectX::XMMATRIX matrixView; // ビュー行列
	void UpdateViewMatrix();

public:
	CameraObject();
	~CameraObject();
	void Init() override;
	void Update() override;
};

