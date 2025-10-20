#pragma once
#include "../GameObject.h"

class GameObject3D : public GameObject
{
private:


public:
	void Init() override;
	void Update() override;
	void Draw() override;
};