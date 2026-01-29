#pragma once

#include "../../99-Lib/01-MyLib/08-Scene/01-Scenes/00-BaseScene/BaseScene.h"

class Hew_TitleScene : public BaseScene
{
private:
	GameObject2D BGImg;

public:

	void Init() override;
	void UnInit() override;
};