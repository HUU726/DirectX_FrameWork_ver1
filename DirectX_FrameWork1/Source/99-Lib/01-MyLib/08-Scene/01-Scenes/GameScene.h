#pragma once
#include "./00-BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
private:
	int	flameCnt;	//フレームカウント

public:
	void Init() override;
	void UnInit() override;
};

