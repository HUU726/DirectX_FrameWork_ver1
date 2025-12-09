#pragma once

#include "../../../99-CompMng/IF_ComponentManager.h"
#include "../../00-Collider/Collider.h"
#include <vector>
#include <unordered_set>

using ColliderPair = std::pair<Collider*, Collider*>;

struct PairHash
{
	size_t operator()(const ColliderPair& _pair) const noexcept
	{
		return std::hash<Collider*>()(_pair.first) ^ (std::hash<Collider*>()(_pair.second) << 1);
	}
};

struct PairEq
{
	bool operator()(const ColliderPair& _pairA, const ColliderPair& _pairB) const noexcept
	{
		return (_pairA.first == _pairB.first && _pairA.second == _pairB.second);
	}
};

using PairSet = std::unordered_set<ColliderPair, PairHash, PairEq>;


template<class T>
class ColliderManager : public IF_ComponentManager
{
protected:
	using Self = ColliderManager<T>;

	std::vector<T*> li_collider;
	std::vector<T*> li_enableCol;

	std::vector<ColliderPair> li_curCollisionPair;
	std::vector<ColliderPair> li_preCollisionPair;

	void OnCollisionEnter(Collider* _p_colliderA, Collider* _p_colliderB);
	void OnCollisionStay(Collider* _p_colliderA, Collider* _p_colliderB);
	void OnCollisionExit(Collider* _p_colliderA, Collider* _p_colliderB);

	void CheckPair();

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
inline void ColliderManager<T>::CheckPair()
{


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