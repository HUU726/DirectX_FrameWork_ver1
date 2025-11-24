#pragma once


#include <vector>

template<class T>
class CompornentManager
{
private:
	std::vector<T*> compornents;

	CompornentManager<T>();

public:
	static CompornentManager<T>& GetInstance()
	{
		static CompornentManager<T> instance;
		return instance;
	}

	void Add(T* _p_comp) { compornents.push_back(_p_comp); }
	void Delete(T* _p_comp);

	void Action();
};


