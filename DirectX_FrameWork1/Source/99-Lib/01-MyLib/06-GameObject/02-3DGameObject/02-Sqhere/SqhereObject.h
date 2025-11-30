#pragma once

#include "../../02-3DGameObject/GameObject3D.h"



class SqhereObject : public GameObject3D
{
private:


public:
	SqhereObject();


	void Init() override;
	void Update() override;
};

