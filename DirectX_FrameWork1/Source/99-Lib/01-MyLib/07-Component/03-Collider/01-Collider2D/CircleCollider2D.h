#pragma once
#include "./00-Collider2D/Collider2D.h"

class CircleCollider2D : public Collider2D
{
private:
	float radius;	//”¼Œa

public:
	bool CollideWith(Collider2D* _collider) override;
	bool CollideWithBox(Collider2D* _box) override;
	bool CollideWithCircle(Collider2D* _circle) override;
	bool CollideWithLine(Collider2D* _line) override;

	float GetRadius() const { return radius; }

	void Init() override;
	void Update() override;
};

