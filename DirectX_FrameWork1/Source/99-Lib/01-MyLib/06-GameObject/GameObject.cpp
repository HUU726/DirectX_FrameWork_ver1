#include "GameObject.h"

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


#include "../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"

void GameObject::SetIsActive(bool _is)
{
	for (auto& comp : li_comp)
	{
		auto compPtr = comp.get();
		if (auto renderer2D = dynamic_cast<SpriteRenderer*>(compPtr))
			continue;
		if (auto renderer3D = dynamic_cast<MeshRenderer*>(compPtr))
			continue;

		comp->SetIsActive(_is);
	}
}

void GameObject::SetIsRender(bool _is)
{
	for (auto& comp : li_comp)
	{
		auto compPtr = comp.get();
		if (auto renderer2D = dynamic_cast<SpriteRenderer*>(compPtr))
			renderer2D->SetIsActive(_is);
		if (auto renderer3D = dynamic_cast<MeshRenderer*>(compPtr))
			renderer3D->SetIsActive(_is);
	}
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
