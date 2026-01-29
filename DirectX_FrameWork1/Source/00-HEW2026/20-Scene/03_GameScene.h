#pragma once


#include "../../99-Lib/01-MyLib/08-Scene/01-Scenes/00-BaseScene/BaseScene.h"
#include "../02-UI/UIManager.h"

class Hew_GameScene : public BaseScene
{
private:
	StagePlayUIManager _UI;

public:

	void Init() override;
	void UnInit() override;

};