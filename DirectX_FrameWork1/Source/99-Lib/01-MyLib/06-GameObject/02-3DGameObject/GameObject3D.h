#pragma once
#include "../GameObject.h"

class GameObject3D : public GameObject
{
private:


public:
	GameObject3D();
	void Init() override;
	void Update() override;
	void Draw() override;
};