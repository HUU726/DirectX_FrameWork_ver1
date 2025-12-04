#pragma once

#include "../../06-GameObject/01-2DGameObject/GameObject2D.h"

class TestAnimation2D : public GameObject2D
{
private:

public:
	TestAnimation2D();
	void Init() override;
	void Update() override;

};

