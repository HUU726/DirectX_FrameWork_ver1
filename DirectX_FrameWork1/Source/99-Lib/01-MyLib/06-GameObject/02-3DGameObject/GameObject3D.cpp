#include "GameObject3D.h"

#include "../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"

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
