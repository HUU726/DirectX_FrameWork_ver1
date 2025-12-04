#pragma once

#include "./IF_ComponentManager.h"

#include <vector>
#include "../../01-System/System.h"


#include "../02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../02-Renderer/02-MeshRenderer/MeshRenderer.h"
#include "../03-Collider/01-Collider2D/00-Collider2D/Collider2D.h"
#include "../03-Collider/02-Collider3D/00-Collider3D/Collider3D.h"
#include "../04-Camera/01-Camera2D/Camera2D.h"
#include "../04-Camera/02-Camera3D/Camera3D.h"
#include "../05-Light/Light.h"
#include "../06-Animator/01-SpriteAnimator/SpriteAnimator.h"


template<class T>
class ComponentManager : public IF_ComponentManager
{
private:
	using Self = ComponentManager<T>;

	std::vector<T*> components;	//コンポネント格納コンテナ

	ComponentManager();

public:
	static Self& GetInstance()
	{
		static Self instance;
		return instance;
	}

	void Add(T* _p_comp) { components.push_back(_p_comp); }
	void Remove(T* _p_comp)
	{
		auto it = std::find(components.begin(), components.end(), _p_comp);
		if ( it != components.end() )
		{
			components.erase(it);
		}
	}
	void AllRemove()
	{
		components.clear();
	}

	/**
	* @brief	コンポネント別のAction関数を呼び出す
	*/
	void Action() override;

};



template<class T>
void ComponentManager<T>::Action()
{
	{
		for (auto& comp : components)
		{
			if (!comp->GetIsActive())
				continue;

			comp->Action();
		}
	}
}

template<class T>
ComponentManager<T>::ComponentManager()
{

}


template<>
ComponentManager<Collider2D>::ComponentManager();
template<>
void ComponentManager<Collider2D>::Action();


template<>
ComponentManager<Collider3D>::ComponentManager();
template<>
void ComponentManager<Collider3D>::Action();


template<>
ComponentManager<SpriteAnimator>::ComponentManager();


template<>
ComponentManager<Camera3D>::ComponentManager();


template<>
ComponentManager<Camera2D>::ComponentManager();


template<>
ComponentManager<Light>::ComponentManager();


template<>
ComponentManager<MeshRenderer>::ComponentManager();


template<>
ComponentManager<SpriteRenderer>::ComponentManager();