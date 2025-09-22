#include "GameObject.h"
#include "../99-Lib/01-MyLib/97-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"
#include "../99-Lib/01-MyLib/97-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../99-Lib/01-MyLib/97-Component/01-Transform/Transform.h"

GameObject::GameObject()
{
  	transform = AddComponent<Transform>();
	isActive = true;
	isRender = true;
}

GameObject::~GameObject()
{
}


void GameObject::InitComponent()
{
	for (auto& comp : this->li_comp)
		comp->Init();
}

void GameObject::UpdateComponent()
{
	if (!isActive)
		return;

	for (auto& comp : this->li_comp)
		comp->Update();
}

void GameObject::Draw()
{
	if (!isRender)
		return;

	if (auto comp = GetComponent<MeshRenderer>())
		comp->Draw();
	if (auto comp = GetComponent<SpriteRenderer>())
		comp->Draw();
}
