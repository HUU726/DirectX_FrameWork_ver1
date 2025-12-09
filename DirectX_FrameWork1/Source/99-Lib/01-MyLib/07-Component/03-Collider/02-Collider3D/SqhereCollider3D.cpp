#include "SqhereCollider3D.h"

#include "../../../06-GameObject/GameObject.h"


bool SqhereCollider3D::CollideWith(Collider3D* _p_col)
{
    return _p_col->CollideWithSqhere(this);
}

bool SqhereCollider3D::CollideWithBox(Collider3D* _p_col)
{
    return ::BoxSqhere(_p_col, this);
}

bool SqhereCollider3D::CollideWithSqhere(Collider3D* _p_col)
{
    return ::SqhereSqhere(this, _p_col);
}

bool SqhereCollider3D::CollideWithMesh(Collider3D* _p_col)
{
    return ::SqhereMesh(this, _p_col);
}

void SqhereCollider3D::Init()
{
    InitCallbackFunc();
    Transform transform = gameObject->GetTransform();
    position = transform.position;
    size = transform.scale;
	radius = transform.scale.x / 2.0f;
}

void SqhereCollider3D::Update()
{
    const Transform& transform = gameObject->GetTransform();
    position = transform.position;
}
