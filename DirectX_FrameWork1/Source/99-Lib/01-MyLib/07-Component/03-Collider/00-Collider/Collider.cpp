#include "Collider.h"

#include "../../../06-GameObject/GameObject.h"


/**
* @brief	所属GameObjectのOnCollision系関数を取得
* @note		Collider派生先の末端コライダーで呼び出す
*/
void Collider::InitCallbackFunc()
{
	funcOnCollisionEnter = [this](Collider* _p_collider){(gameObject->OnCollisionEnter(_p_collider));};
	funcOnCollisionStay = [this](Collider* _p_collider){(gameObject->OnCollisionStay(_p_collider)); };
	funcOnCollisionExit = [this](Collider* _p_collider){(gameObject->OnCollisionExit(_p_collider)); };
}

Collider::Collider()
{
	offset = { 0,0 };
	size = { 0,0 };
	isTrigger = false;

	funcOnCollisionEnter = nullptr;
	funcOnCollisionStay = nullptr;
	funcOnCollisionExit = nullptr;
}

void Collider::AddCurHitCollider(Collider* _p_collider)
{
	curHitColliders.push_back(_p_collider);
}

void Collider::SwapHitColliders()
{
	preHitColliders.clear();
	curHitColliders.swap(preHitColliders);
}

void Collider::CheckHitColliders()
{

	if ( curHitColliders.size() == 0 )
	{
		for ( auto preCollider : preHitColliders )
		{
			OnCollisionExit(preCollider);
		}
	}
	else
	{
		for ( auto curCollider : curHitColliders )
		{
			//現フレームでヒットしているコライダが前フレームでヒットしているか？
			if ( std::find(preHitColliders.begin(), preHitColliders.end(), curCollider) == preHitColliders.end() )
			{
				OnCollisionEnter(curCollider);
			}

			for ( auto preCollider : preHitColliders )
			{
				//現フレームと前フレームで同コライダがヒットしているか
				if ( curCollider == preCollider )
				{
					OnCollisionStay(curCollider);
					continue;
				}
				//前フレームでヒットしているコライダが現フレームでヒットしているか
				if ( std::find(curHitColliders.begin(), curHitColliders.end(), preCollider) == curHitColliders.end() )
				{
					OnCollisionExit(preCollider);
				}

			}
		}
	}


}

void Collider::OnCollisionEnter(Collider* _p_collider)
{
	if (funcOnCollisionEnter != nullptr)
		funcOnCollisionEnter(_p_collider);
}
void Collider::OnCollisionStay(Collider* _p_collider)
{
	if (funcOnCollisionStay != nullptr)
		funcOnCollisionStay(_p_collider);
}
void Collider::OnCollisionExit(Collider* _p_collider)
{
	if (funcOnCollisionExit != nullptr)
		funcOnCollisionExit(_p_collider);
}