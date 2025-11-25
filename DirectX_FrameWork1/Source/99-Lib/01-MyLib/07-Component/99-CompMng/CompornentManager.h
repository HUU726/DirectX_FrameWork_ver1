#pragma once

#include "./IF_ComponentManager.h"

#include <vector>

template<class T>
class CompornentManager : public Base_ComponentManager
{
private:
	using Base = T;
	using Self = CompornentManager<T>;

	std::vector<T*> compornents;

	CompornentManager() {}

public:
	static CompornentManager<T>& GetInstance()
	{
		static CompornentManager<T> instance;
		return instance;
	}

	void Add(T* _p_comp) { compornents.push_back(_p_comp); }
	void Delete(T* _p_comp)
	{
		auto it = std::find(compornents.begin(), compornents.end(), _p_comp);
		if ( it != compornents.end() )
		{
			compornents.erase(it);
		}
	}

	void Action()
	{
		for ( auto& comp : compornents )
		{
			if ( !comp->GetIsActive() )
				continue;

			comp->Action();
		}
	}
};


