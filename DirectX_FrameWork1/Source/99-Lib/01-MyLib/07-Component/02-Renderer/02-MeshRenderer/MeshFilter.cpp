#include "./01-Shape/01-Cube/Cube.h"
#include "MeshFilter.h"

#include "../../../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"


/********************************************************
*		MeshFilter
********************************************************/
#include "../../../06-GameObject/GameObject.h"

MeshFilter::MeshFilter()
{

}

MeshFilter::MeshFilter(hft::Mesh& _mesh)
{

}

MeshFilter::MeshFilter(hft::Sprite2D& _sprite)
{

}

MeshFilter::~MeshFilter()
{

}

std::shared_ptr<hft::Mesh> MeshFilter::SetMesh(std::string _name)
{
	sp_mesh = ShapeTable3D::GetInstance().GetShape(_name);
	return sp_mesh;
}

std::shared_ptr<hft::Mesh> MeshFilter::SetMesh(std::shared_ptr<hft::Mesh> _sp_mesh)
{
	sp_mesh = ShapeTable3D::GetInstance().GetShape(_sp_mesh->name);
	return sp_mesh;
}

void MeshFilter::Init()
{
}

//void MeshFilter::Init()
//{
//	if (mesh != nullptr)
//	{
//		Transform* transform = &gameObject->GetTransform();
//		if (mesh->GetIsCreate())
//		{
//			transform->position = mesh->GetTransform().position;
//			transform->rotation = mesh->GetTransform().rotation;
//			transform->scale = mesh->GetTransform().scale;
//		}
//		mesh->setTransform(transform);
//	}
//	
//	if (sprite != nullptr)
//	{
//		Transform* transform = &gameObject->GetTransform();
//		if (sprite->GetIsCreate())
//		{
//			transform->position = sprite->getTransform().position;
//			transform->rotation = sprite->getTransform().rotation;
//			transform->scale = sprite->getTransform().scale;
//		}
//		sprite->setTransform(transform);
//	}
//}