#include "SqhereObject.h"

#include "../../../998-FH_Types/TransformMatrix.h"
#include "../../../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"
#include "../../../07-Component/03-Collider/02-Collider3D/SqhereCollider3D.h"



SqhereObject::SqhereObject()
{

}

void SqhereObject::Init()
{
	auto sp_shape = ShapeTable3D::GetInstance().GetShape("sqhere");
	auto mesh = GetComponent<MeshRenderer>()->SetShape(sp_shape);

	AddComponent<SqhereCollider3D>();
}

void SqhereObject::Update()
{
}
