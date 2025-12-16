#pragma once

#include "./00-BaseScene/BaseScene.h"
#include "../../06-GameObject/02-3DGameObject/02-Sqhere/SqhereObject.h"

class GameScene : public BaseScene
{
private:
	int	flameCnt;	//フレームカウント
	SqhereObject sqhereObj;

public:
	void Init() override;
	void UnInit() override;
};

