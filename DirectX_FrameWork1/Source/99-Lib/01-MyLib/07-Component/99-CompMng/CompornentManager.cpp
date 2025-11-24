#include "CompornentManager.h"


template<class T>
void CompornentManager<T>::Delete(T* _p_comp)
{
	auto targetObject = _p_comp->GetGameObject();
	int targetID = targetObject->GetID();

	for ( auto it = compornents.begin(); it != compornents.end(); it++)
	{
		auto object = it->GetGameObject();
		int id = object->GetID();
		if (targetID == id)
		{
			compornents.erase(it);
			break;
		}
	}
}

template<class T>
void CompornentManager<T>::Action()
{
	for ( auto& comp : compornents )
	{
		if (!comp->GetIsActive())
			continue;

		comp->Action();
	}
}
