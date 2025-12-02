#pragma once

#include "../GameObject3D.h"

class PlaneObject : public GameObject3D
{
protected:


public:
	PlaneObject();

	void OnCollisionEnter(Collider* _p_collider) override;

	void Init() override;
	void Update() override;

};

