#include "PlaneObject.h"


#include "../../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"
#include "../../../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../../../07-Component/03-Collider/02-Collider3D/MeshCollider3D.h"

PlaneObject::PlaneObject()
{
	auto mesh = GetComponent<MeshRenderer>()->GetShape();
	mesh = ShapeTable3D::GetInstance().GetShape("plane");

	AddComponent<MeshCollider3D>();
}
