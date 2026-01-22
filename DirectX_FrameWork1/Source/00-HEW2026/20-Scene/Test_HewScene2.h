#pragma once

#include "../../99-Lib/01-MyLib/08-Scene/01-Scenes/00-BaseScene/BaseScene.h"

#include "../10-Map/00-BaseMap/BaseMap.h"
#include "../01-GamaeObject/100-Test/HewTestGameObject.h"


class Test_HewScene2 : public BaseScene
{
private:
	ObjectS2 obj;

public:
	void Init() override;
	void UnInit() override;
};