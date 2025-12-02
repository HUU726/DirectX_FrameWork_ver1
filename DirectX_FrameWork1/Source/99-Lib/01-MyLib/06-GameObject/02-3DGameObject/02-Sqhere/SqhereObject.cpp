#include "SqhereObject.h"

#include <iostream>

#include "../../../998-FH_Types/TransformMatrix.h"
#include "../../../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"
#include "../../../07-Component/03-Collider/02-Collider3D/SqhereCollider3D.h"



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
