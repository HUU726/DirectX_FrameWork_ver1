#pragma once
#include "./00-BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
private:
	int	flameCnt;	//フレームカウント

public:
	void Init() override;
	void Input() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;
};

