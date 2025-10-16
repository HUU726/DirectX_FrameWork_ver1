#pragma once
#include "./00-BaseScene/BaseScene.h"


class TitleScene : public BaseScene
{
private:
	int	flameCnt;	// フレームカウント
	CameraObject2D camera2D;
	GameObject2D gameObject;

public:

	void Init() override;
	void Input() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

};

