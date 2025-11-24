#include "BoxCollider3D.h"
#include "../99-ColliderManager/02-Collider3DManager/Collider3DManager.h"
#include "../../../06-GameObject/GameObject.h"
#include "../../../998-FH_Types/TransformMatrix.h"

bool BoxCollider3D::CollideWith(Collider3D* _p_col)
{
    return _p_col->CollideWithBox(this);
}

bool BoxCollider3D::CollideWithBox(Collider3D* _p_col)
{
    return ::BoxBox(this, _p_col);
}

bool BoxCollider3D::CollideWithSqhere(Collider3D* _p_col)
{
    return ::BoxSqhere(this, _p_col);
}

bool BoxCollider3D::CollideWithMesh(Collider3D* _p_col)
{
    return ::BoxMesh(this, _p_col);
}

void BoxCollider3D::Init()
{
	Transform transform(gameObject->GetTransform());
    position = transform.position;
    size = transform.scale;
}

void BoxCollider3D::Update()
{
    Transform transform = gameObject->GetTransform();
    position = transform.position;
    size = transform.scale;
}
