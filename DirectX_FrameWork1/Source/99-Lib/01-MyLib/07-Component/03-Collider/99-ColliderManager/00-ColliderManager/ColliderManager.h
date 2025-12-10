#pragma once

#include "../../../99-CompMng/IF_ComponentManager.h"
#include "../../00-Collider/Collider.h"
#include <vector>
#include <unordered_set>



/*******************************************************************************************
*		ハッシュ管理用
*******************************************************************************************/
using ColliderPair = std::pair<Collider*, Collider*>;



struct PairHash
{
	//コライダー同士のハッシュを組み合わせてペア用ハッシュ生成
	size_t operator()(const ColliderPair& _pair) const noexcept
	{
		return std::hash<Collider*>()(_pair.first) ^ (std::hash<Collider*>()(_pair.second) << 1); //シフトしてハッシュ値の衝突回避
	}
};

struct PairEq
{
	//ハッシュが衝突した際に呼ばれる、キー比較
	bool operator()(const ColliderPair& _pairA, const ColliderPair& _pairB) const noexcept
	{
		return (_pairA.first == _pairB.first && _pairA.second == _pairB.second) ||
				(_pairA.second == _pairB.first && _pairA.first == _pairB.second);
	}
};

using PairSet = std::unordered_set<ColliderPair, PairHash, PairEq>; //2つのコライダーをハッシュに持つテーブル








/*******************************************************************************************
*		コライダーマネージャー
*******************************************************************************************/
template<class T>
class ColliderManager : public IF_ComponentManager
{
protected:
	using Self = ColliderManager<T>;

	std::vector<T*> li_collider;
	std::vector<T*> li_enableCol;

	PairSet curColliderPair;
	PairSet preColliderPair;

	void OnCollisionEnter(const ColliderPair& _colliderPair);
	void OnCollisionStay(const ColliderPair& _colliderPair);
	void OnCollisionExit(const ColliderPair& _colliderPair);

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




/*******************************************************************************************
*		テンプレート共通処理
*******************************************************************************************/

/**
* @brief	衝突時にペアになっているColliderのOnCollisionEnterを呼び出す
* @param	ColliderPair	_colliderPair
*/
template<class T>
inline void ColliderManager<T>::OnCollisionEnter(const ColliderPair& _colliderPair)
{
	auto& colliderA = _colliderPair.first;
	auto& colliderB = _colliderPair.second;

	colliderA->OnCollisionEnter(colliderB);
	colliderB->OnCollisionEnter(colliderA);
}
/**
* @brief	ペアになっているColliderのOnCollisionStayを呼び出す
*/
template<class T>
inline void ColliderManager<T>::OnCollisionStay(const ColliderPair& _colliderPair)
{
	auto& colliderA = _colliderPair.first;
	auto& colliderB = _colliderPair.second;

	colliderA->OnCollisionStay(colliderB);
	colliderB->OnCollisionStay(colliderA);
}
template<class T>
inline void ColliderManager<T>::OnCollisionExit(const ColliderPair& _colliderPair)
{
	auto& colliderA = _colliderPair.first;
	auto& colliderB = _colliderPair.second;

	colliderA->OnCollisionExit(colliderB);
	colliderB->OnCollisionExit(colliderA);
}

template<class T>
inline void ColliderManager<T>::CheckPair()
{
	for ( auto& p : curColliderPair )
	{
		if ( preColliderPair.find(p) == preColliderPair.end() )
		{
			OnCollisionEnter(p);
		}
		else
		{
			OnCollisionStay(p);
		}
	}

	for ( auto& p : preColliderPair )
	{
		if ( curColliderPair.find(p) == curColliderPair.end() )
		{
			OnCollisionExit(p);
		}
	}

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