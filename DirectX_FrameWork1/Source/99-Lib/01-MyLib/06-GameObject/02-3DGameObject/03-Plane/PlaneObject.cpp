#include "PlaneObject.h"


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
