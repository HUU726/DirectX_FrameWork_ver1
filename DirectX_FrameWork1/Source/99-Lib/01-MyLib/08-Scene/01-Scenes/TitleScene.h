#pragma once
#include "./00-BaseScene/BaseScene.h"


class TitleScene : public BaseScene
{
private:
	int	flameCnt;	// フレームカウント
	CameraObject2D camera2D;
	CameraObject3D camera3D;

	LightObject lightObject;

	GameObject2D gameObject2D;
	GameObject3D sqhereObject;
	GameObject3D planeObject;
	GameObject3D cubeObject;


public:

	void Init() override;
	void Input() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

};

