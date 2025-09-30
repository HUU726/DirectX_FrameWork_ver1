#include "GameObject.h"
#include "../07-Component/01-Transform/Transform.h"

GameObject::GameObject()
{
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
