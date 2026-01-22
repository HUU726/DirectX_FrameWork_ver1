#pragma once

#include "../../../99-Lib/01-MyLib/06-GameObject/GameObject.h"


class ObjectS1 : public GameObject
{
public:

	void Init() override;
	void Update() override;
};

class ObjectS2 : public GameObject
{
public:
	void Init();
	void Update();
};