#pragma once
#include "../GameObject.h"

class GameObject2D : public GameObject
{

public:
	GameObject2D();
	void Init() override;
	void Update() override;
	void Draw() override;
};

