#pragma once
#include "../GameObject.h"

class GameObject2D : public GameObject
{

public:
	void Init() override;
	void Update() override;
	void Draw() override;
};

