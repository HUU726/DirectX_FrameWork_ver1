#pragma once
#include "00-BaseScene/BaseScene.h"

class StageSelectScene : public BaseScene
{
private:
    GameObject* pLogic = nullptr;
public:
    void Init() override;
    void UnInit() override;
};