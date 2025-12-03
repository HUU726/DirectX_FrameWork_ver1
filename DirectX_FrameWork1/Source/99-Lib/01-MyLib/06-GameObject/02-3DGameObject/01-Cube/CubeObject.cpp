#include "CubeObject.h"

#include "../../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"
#include "../../../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../../../07-Component/03-Collider/02-Collider3D/BoxCollider3D.h"


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
