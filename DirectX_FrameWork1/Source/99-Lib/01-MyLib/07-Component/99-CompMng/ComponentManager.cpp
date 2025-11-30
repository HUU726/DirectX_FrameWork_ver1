#include "ComponentManager.h"

template<>
ComponentManager<Collider2D>::ComponentManager()
{
	type = COMP_MNG_TYPES::COMP_COLLIDER2D;
	System::GetInstance().AddCompMng(this);
}

template<>
ComponentManager<Collider3D>::ComponentManager()
{
	type = COMP_MNG_TYPES::COMP_COLLIDER3D;
	System::GetInstance().AddCompMng(this);
}

template<>
ComponentManager<SpriteAnimator>::ComponentManager()
{
	type = COMP_MNG_TYPES::COMP_ANIMATOR;
	System::GetInstance().AddCompMng(this);
}

template<>
ComponentManager<Camera3D>::ComponentManager()
{
	type = COMP_MNG_TYPES::COMP_CAMERA3D;
	System::GetInstance().AddCompMng(this);
}

template<>
ComponentManager<Camera2D>::ComponentManager()
{
	type = COMP_MNG_TYPES::COMP_CAMERA2D;
	System::GetInstance().AddCompMng(this);
}

template<>
ComponentManager<Light>::ComponentManager()
{
	type = COMP_MNG_TYPES::COMP_LIGHT;
	System::GetInstance().AddCompMng(this);
}

template<>
ComponentManager<MeshRenderer>::ComponentManager()
{
	type = COMP_MNG_TYPES::COMP_RENDERER3D;
	System::GetInstance().AddCompMng(this);
}

template<>
ComponentManager<SpriteRenderer>::ComponentManager()
{
	type = COMP_MNG_TYPES::COMP_RENDERER2D;
	System::GetInstance().AddCompMng(this);
}