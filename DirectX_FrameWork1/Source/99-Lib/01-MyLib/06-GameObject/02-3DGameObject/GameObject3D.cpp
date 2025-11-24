#include "GameObject3D.h"

#include "../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"

GameObject3D::GameObject3D()
{
	AddComponent<MeshRenderer>();
	p_transform->position = {0,0,0};
	p_transform->rotation = {0,0,0};
	p_transform->scale = {100,100,100};
}

void GameObject3D::Init()
{
}

void GameObject3D::Update()
{
}

void GameObject3D::Draw()
{
	if (const auto& comp = GetComponent<MeshRenderer>())
		comp->Draw();
}
