#include "CubeObject.h"


CubeObject::CubeObject()
{

}

void CubeObject::Init()
{
	auto mesh = GetComponent<MeshRenderer>()->GetShape();
	mesh = ShapeTable3D::GetInstance().GetShape("cube");

	AddComponent<BoxCollider3D>();
}

void CubeObject::Update()
{
}
