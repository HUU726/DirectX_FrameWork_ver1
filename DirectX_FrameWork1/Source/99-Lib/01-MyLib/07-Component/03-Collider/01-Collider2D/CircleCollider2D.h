#pragma once
#include "Collider2D.h"

class CircleCollider2D : public Collider2D
{
private:
	GEN_COMPONENT_ID(CircleCollider2D)
public:
	bool CollideWith(Collider2D* _collider) override;
	bool CollideWithBox(Collider2D* _box) override;
	bool CollideWithCircle(Collider2D* _circle) override;
	bool CollideWithLine(Collider2D* _line) override;

	void Init() override;
};

