#pragma once

#include "../GameObject3D.h"

class CubeObject : public GameObject3D
{
protected:



public:
	CubeObject();

	void Init() override;
	void Update() override;

};

