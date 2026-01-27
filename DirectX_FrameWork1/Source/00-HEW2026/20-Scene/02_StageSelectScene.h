#pragma once
#include "../../99-Lib/01-MyLib/08-Scene/01-Scenes/00-BaseScene/BaseScene.h"

class Hew_StageSelectScene : public BaseScene
{
private:
    GameObject* pLogic = nullptr;
public:
    void Init() override;
    void UnInit() override;
};