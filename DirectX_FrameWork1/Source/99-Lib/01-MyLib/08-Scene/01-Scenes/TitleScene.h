#pragma once
#include "./00-BaseScene/BaseScene.h"

#include "../../1000-Test/TestModel/TestModel.h"
#include "../../06-GameObject/301-GroundObject/GroundObject.h"
#include "../../1000-Test/TestPlayer/TestPlayer.h"
#include "../../1000-Test/TestAnimation2D/TestAnimation2D.h"
#include "../../1000-Test/TestEnemy/TestEnemy.h"

class TitleScene : public BaseScene
{
private:
	int	flameCnt;	// フレームカウント
	CameraObject2D camera2D;
	CameraObject3D camera3D;

	LightObject lightObject;

	GameObject3D sqhereObject;
	GameObject3D planeObject;
	GameObject3D cubeObject;

	TestModel testModel;
	GroundObject groundObject;
	TestPlayer testPlayer;
	TestEnemy testEnemy;
	TestAnimation2D testAnimation2D;

public:
	~TitleScene() override;

	void Init() override;
	void Input() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

};

