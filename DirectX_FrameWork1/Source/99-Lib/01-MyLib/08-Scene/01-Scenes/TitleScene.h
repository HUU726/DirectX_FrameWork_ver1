#pragma once
#include "./00-BaseScene/BaseScene.h"

#include "../../1000-Test/TestModel/TestModel.h"
#include "../../06-GameObject/301-GroundObject/GroundObject.h"
#include "../../1000-Test/TestPlayer/TestPlayer.h"
#include "../../1000-Test/TestAnimation2D/TestAnimation2D.h"
#include "../../1000-Test/TestEnemy/TestEnemy.h"


#include "../../06-GameObject/02-3DGameObject/01-Cube/CubeObject.h"
#include "../../06-GameObject/02-3DGameObject/02-Sqhere/SqhereObject.h"
#include "../../06-GameObject/02-3DGameObject/03-Plane/PlaneObject.h"


class TitleScene : public BaseScene
{
private:
	SqhereObject sqhereObject;
	PlaneObject planeObject;
	CubeObject cubeObject;

	TestModel testModel;
	GroundObject groundObject;
	TestPlayer testPlayer;
	TestEnemy testEnemy;
	TestAnimation2D testAnimation2D;

public:
	~TitleScene() override;

	void Init() override;
	void UnInit() override;

};

