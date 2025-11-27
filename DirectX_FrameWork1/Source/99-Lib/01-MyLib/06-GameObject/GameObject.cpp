#include "GameObject.h"
#include "../07-Component/01-Transform/Transform.h"
#include "./999-GameObjectManager/GameObjectManager.h"

GameObject::GameObject()
{
	GameObjectManager::GetInstance().AddGameObject(this);

	p_transform = AddComponent<Transform>();
	isActive = true;
	isRender = true;
}

GameObject::~GameObject()
{
	GameObjectManager::GetInstance().RemoveGameObject(this);
	AllDeleteComponent();
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
