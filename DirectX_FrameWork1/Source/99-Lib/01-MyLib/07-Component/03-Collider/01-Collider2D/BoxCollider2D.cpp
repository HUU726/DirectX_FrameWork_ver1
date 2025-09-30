#include "BoxCollider2D.h"
#include "../../../06-GameObject/GameObject.h"
#include "../99-ColliderManager/01-Collider2DManager/Collider2DManager.h"

bool BoxCollider2D::CollideWith(Collider2D* _p_collider)
{
	return _p_collider->CollideWithBox(this);
}

bool BoxCollider2D::CollideWithBox(Collider2D* _box)
{
	return ::BoxBox(this, _box);
}

bool BoxCollider2D::CollideWithCircle(Collider2D* _circle)
{
	return ::BoxCircle(this, _circle);
}

bool BoxCollider2D::CollideWithLine(Collider2D* _line)
{
	return ::BoxLine(this, _line);
}

void BoxCollider2D::Init()
{
	Collider2DManager::GetInstance().AddCollider(this);
	Transform transform = gameObject->GetTransform();
	position = transform.position;
	size = transform.scale;
}

void BoxCollider2D::Update()
{
	position = gameObject->GetTransform().position;
	size = gameObject->GetTransform().scale;
}
