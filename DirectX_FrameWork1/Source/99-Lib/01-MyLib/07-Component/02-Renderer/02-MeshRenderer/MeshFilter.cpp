#include "Mesh.h"
#include "./01-Shape/01-Cube/Cube.h"



/********************************************************
*		MeshFilter
********************************************************/
#include "../../../06-GameObject/GameObject.h"

MeshFilter::MeshFilter()
{
	mesh = new Cube;
	sprite = nullptr;
}

MeshFilter::MeshFilter(Mesh& _mesh)
{
	mesh = new Mesh;
	*mesh = _mesh;
	sprite = nullptr;
}

MeshFilter::MeshFilter(Sprite2D& _sprite)
{
	sprite = new Sprite2D;
	
	mesh = nullptr;
	*sprite = _sprite;
}

MeshFilter::~MeshFilter()
{
	if (mesh != nullptr)
	{
		delete mesh;
		mesh = nullptr;
	}
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
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