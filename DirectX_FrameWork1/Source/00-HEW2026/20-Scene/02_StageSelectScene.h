#pragma once
#include "../../99-Lib/01-MyLib/08-Scene/01-Scenes/00-BaseScene/BaseScene.h"

#include "../02-UI/UIManager_Select.h"

class Hew_StageSelectScene : public BaseScene
{
private:
    StageSelectUIManager uiMng;

public:
    void Init() override;
    void UnInit() override;
};