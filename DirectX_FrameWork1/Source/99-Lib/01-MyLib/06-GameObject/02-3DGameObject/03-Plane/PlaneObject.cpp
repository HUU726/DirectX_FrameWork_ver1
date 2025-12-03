#include "PlaneObject.h"

#include "../../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"
#include "../../../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../../../07-Component/03-Collider/02-Collider3D/MeshCollider3D.h"


PlaneObject::PlaneObject()
{

}

void PlaneObject::OnCollisionEnter(Collider* _p_collider)
{
	std::cout << "Plane‚ªÕ“Ë‚µ‚½" << std::endl;
}

void PlaneObject::Init()
{
	auto sp_shape = ShapeTable3D::GetInstance().GetShape("plane");
	GetComponent<MeshRenderer>()->SetShape(sp_shape);

	auto collider = AddComponent<MeshCollider3D>();
}

void PlaneObject::Update()
{
}
