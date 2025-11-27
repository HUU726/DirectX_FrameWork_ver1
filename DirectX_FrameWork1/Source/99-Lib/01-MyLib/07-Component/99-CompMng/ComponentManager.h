#pragma once

#include "./IF_ComponentManager.h"

#include <vector>
#include "../../01-System/System.h"


template<class T>
class ComponentManager : public IF_ComponentManager
{
private:
	using Self = ComponentManager<T>;

	std::vector<T*> compornents;

	ComponentManager()
	{
		System::GetInstance().AddCompMng(this);
	}

public:
	static Self& GetInstance()
	{
		static Self instance;
		return instance;
	}

	void Add(T* _p_comp) { compornents.push_back(_p_comp); }
	void Remove(T* _p_comp)
	{
		auto it = std::find(compornents.begin(), compornents.end(), _p_comp);
		if ( it != compornents.end() )
		{
			compornents.erase(it);
		}
	}

	void Action() override;

};



template<class T>
void ComponentManager<T>::Action()
{
	{
		for (auto& comp : compornents)
		{
			if (!comp->GetIsActive())
				continue;

			comp->Action();
		}
	}
}


class Collider2D;
template<>
void ComponentManager<Collider2D>::Action();

class Collider3D;
template<>
void ComponentManager<Collider3D>::Action();