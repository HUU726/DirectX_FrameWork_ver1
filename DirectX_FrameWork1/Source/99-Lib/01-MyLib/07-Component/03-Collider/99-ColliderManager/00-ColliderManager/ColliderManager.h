#pragma once

#include "../../../99-CompMng/IF_ComponentManager.h"
#include "../../00-Collider/Collider.h"
#include <vector>

template<class T>
class ColliderManager : public IF_ComponentManager
{
protected:
	using Self = ColliderManager<T>;

	std::vector<T*> li_collider;
	std::vector<T*> li_enableCol;

	std::vector<std::pair<T*,T*>> li_curCollisionPair;
	std::vector<std::pair<T*,T*>> li_preCollisionPair;



	void OnCollisionEnter(Collider* _p_colliderA, Collider* _p_colliderB);
	void OnCollisionStay(Collider* _p_colliderA, Collider* _p_colliderB);
	void OnCollisionExit(Collider* _p_colliderA, Collider* _p_colliderB);

	ColliderManager();

public:
	static Self& GetInstance()
	{
		static Self instance;
		return instance;
	}

	void AddCollider(T* _p_collider);
	void ClearCollider();
	void RemoveCollider(T* _p_collider);

	void SelectCollider();	//当たり判定をとるコライダを選別
	void CheckCollision();	//当たり判定＆OnCollision系処理実行
	void Action() override;
};

template<class T>
inline void ColliderManager<T>::OnCollisionEnter(Collider* _p_colliderA, Collider* _p_colliderB)
{
	_p_colliderA->OnCollisionEnter(_p_colliderB);
	_p_colliderB->OnCollisionEnter(_p_colliderA);
}
template<class T>
inline void ColliderManager<T>::OnCollisionStay(Collider* _p_colliderA, Collider* _p_colliderB)
{
	_p_colliderA->OnCollisionStay(_p_colliderB);
	_p_colliderB->OnCollisionStay(_p_colliderA);
}
template<class T>
inline void ColliderManager<T>::OnCollisionExit(Collider* _p_colliderA, Collider* _p_colliderB)
{
	_p_colliderA->OnCollisionExit(_p_colliderB);
	_p_colliderB->OnCollisionExit(_p_colliderA);
}

template<class T>
inline void ColliderManager<T>::AddCollider(T* _p_collider)
{
	li_collider.push_back(_p_collider);
}
template<class T>
inline void ColliderManager<T>::ClearCollider()
{
	li_collider.clear();
	li_enableCol.clear();
}
template<class T>
inline void ColliderManager<T>::RemoveCollider(T* _p_collider)
{
	auto it = std::find(li_collider.begin(), li_collider.end(), _p_collider);

	if ( it != li_collider.end() )
	{
		li_collider.erase(it);
	}
}

template<class T>
inline void ColliderManager<T>::Action()
{
	SelectCollider();
	CheckCollision();
}



class Collider2D;
class Collider3D;

template<>
ColliderManager<Collider2D>::ColliderManager();
template<>
void ColliderManager<Collider2D>::SelectCollider();
template<>
void ColliderManager<Collider2D>::CheckCollision();

template<>
ColliderManager<Collider3D>::ColliderManager();
template<>
void ColliderManager<Collider3D>::SelectCollider();
template<>
void ColliderManager<Collider3D>::CheckCollision();