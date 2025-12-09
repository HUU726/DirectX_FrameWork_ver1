#include "BoxCollider2D.h"
#include "../../../06-GameObject/GameObject.h"

#include "../../../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"

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

hft::HFFLOAT3 BoxCollider2D::GetSize() const
{
	return size;
}

void BoxCollider2D::Init()
{
	InitCallbackFunc();
	Transform transform = gameObject->GetTransform();
	position = transform.position;

	auto polygon = ShapeTable2D::GetInstance().GetShape("sprite");
	auto vertices = polygon->vertices;

	for (auto vertex : vertices)
		li_vertexWorldPos.push_back(vertex.position * transform.scale);

	size.x = li_vertexWorldPos[1].x - li_vertexWorldPos[0].x;
	size.y = li_vertexWorldPos[0].y - li_vertexWorldPos[2].y;
}

void BoxCollider2D::Update()
{
	const Transform& transform = gameObject->GetTransform();
	position = transform.position;
}
