#pragma once

#include "../GameObject3D.h"

class PlaneObject : public GameObject3D
{
protected:


public:
	PlaneObject();

	void Init() override;
	void Update() override;

};

