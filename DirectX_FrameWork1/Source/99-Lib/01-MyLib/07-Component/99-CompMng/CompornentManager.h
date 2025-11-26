#pragma once

#include "./IF_ComponentManager.h"

#include <vector>
#include "../../01-System/System.h"


template<class T>
class CompornentManager : public Base_ComponentManager
{
private:
	using Self = CompornentManager<T>;

	std::vector<T*> compornents;

	CompornentManager()
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


