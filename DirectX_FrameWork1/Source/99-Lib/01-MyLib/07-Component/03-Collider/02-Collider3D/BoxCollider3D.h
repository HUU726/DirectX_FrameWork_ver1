#pragma once
#include "./00-Collider3D/Collider3D.h"


class BoxCollider3D : public Collider3D
{
private:
	std::vector<hft::HFFLOAT3> worldPos;

public:
	bool CollideWith(Collider3D* _p_col) override;
	bool CollideWithBox(Collider3D* _p_col) override;
	bool CollideWithSqhere(Collider3D* _p_col) override;
	bool CollideWithMesh(Collider3D* _p_col) override;

	void Init() override;
	void Update() override;
};

