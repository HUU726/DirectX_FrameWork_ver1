#pragma once
#include "./00-Collider2D/Collider2D.h"


class BoxCollider2D : public Collider2D
{
private:

public:
	bool CollideWith(Collider2D* _collider) override;
	bool CollideWithBox(Collider2D* _box) override;
	bool CollideWithCircle(Collider2D* _circle) override;
	bool CollideWithLine(Collider2D* _line) override;

	void Init() override;
	void Update() override;
};

