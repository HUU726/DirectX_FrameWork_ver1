#include "Collider.h"

#include "../../../06-GameObject/GameObject.h"

Collider::Collider()
{
	funcOnCollisionEnter = [this](Collider* _p_collider){(gameObject->OnCollisionEnter(_p_collider));};
	funcOnCollisionStay = [this](Collider* _p_collider){(gameObject->OnCollisionStay(_p_collider)); };
	funcOnCollisionExit = [this](Collider* _p_collider){(gameObject->OnCollisionExit(_p_collider)); };
}