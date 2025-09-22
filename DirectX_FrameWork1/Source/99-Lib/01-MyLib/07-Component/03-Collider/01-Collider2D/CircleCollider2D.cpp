#include "CircleCollider2D.h"
#include "GameObject.h"
#include "Collider2DManager.h"

bool CircleCollider2D::CollideWith(Collider2D* _collider)
{
    return _collider->CollideWithCircle(this);
}

bool CircleCollider2D::CollideWithBox(Collider2D* _box)
{
    return ::BoxCircle(_box, this);
}

bool CircleCollider2D::CollideWithCircle(Collider2D* _circle)
{
    return ::CircleCircle(this, _circle);
}

bool CircleCollider2D::CollideWithLine(Collider2D* _line)
{
    return ::CircleLine(this, _line);
}

void CircleCollider2D::Init()
{
    Collider2DManager::GetInstance().AddCollider(this);
    transform = gameObject->GetTransformPtr();
    position = transform->position;
    size = transform->scale;
}
