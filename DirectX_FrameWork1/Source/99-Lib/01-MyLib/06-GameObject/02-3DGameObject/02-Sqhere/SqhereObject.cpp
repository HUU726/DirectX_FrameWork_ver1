#include "SqhereObject.h"



SqhereObject::SqhereObject()
{

}

void SqhereObject::OnCollisionEnter(Collider* _p_collider)
{
	std::cout << "Sqhere‚ªÕ“Ë‚µ‚½" << std::endl;
}

void SqhereObject::Init()
{
	auto sp_shape = ShapeTable3D::GetInstance().GetShape("sqhere");
	auto mesh = GetComponent<MeshRenderer>()->SetShape(sp_shape);

	AddComponent<SqhereCollider3D>();
}

void SqhereObject::Update()
{
	if (GetAsyncKeyState('K') & 0x8000 )
		p_transform->position.z -= 0.5f;
	if (GetAsyncKeyState('I') & 0x8000 )
		p_transform->position.z += 0.5f;
	if (GetAsyncKeyState('J') & 0x8000 )
		p_transform->position.x -= 0.5f;
	if ( GetAsyncKeyState('L') & 0x8000 )
		p_transform->position.x += 0.5f;
}
