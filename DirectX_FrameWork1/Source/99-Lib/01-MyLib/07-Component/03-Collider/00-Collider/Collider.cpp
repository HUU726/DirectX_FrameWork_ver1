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