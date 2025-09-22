#pragma once
#include "BaseScene.h"
class GameOverScene : public BaseScene
{
private:

public:
	void Init() override;
	void Input() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;
};

