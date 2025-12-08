#pragma once

#include "../../02-3DGameObject/GameObject3D.h"



class SqhereObject : public GameObject3D
{
private:


public:
	SqhereObject();

	void OnCollisionEnter(Collider* _p_collider) override;
	void OnCollisionStay(Collider* _p_collider) override;
	void OnCollisionExit(Collider* _p_collider) override;

	void Init() override;
	void Update() override;
};

