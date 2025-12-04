#pragma once

#include "./00-Collider3D/Collider3D.h"

class SqhereCollider3D : public Collider3D
{
private:
	float radius;	//”¼Œa

public:
	bool CollideWith(Collider3D* _p_col) override;
	bool CollideWithBox(Collider3D* _p_col) override;
	bool CollideWithSqhere(Collider3D* _p_col) override;
	bool CollideWithMesh(Collider3D* _p_col) override;

	float GetRadius() const { return radius; }

	void Init() override;
	void Update() override;
};

