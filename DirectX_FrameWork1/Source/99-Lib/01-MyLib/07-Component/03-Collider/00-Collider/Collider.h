#pragma once

#include "../../00-Component/Component.h"

#include "../../../998-FH_Types/HF_FLOAT.h"
#include <functional>

class Collider;
typedef std::function<void(Collider*)> CallbackOnCollisionFunc;



class Collider : public Component
{
protected:
	hft::HFFLOAT3 offset;
	hft::HFFLOAT3 size;
	bool isTrigger;

	CallbackOnCollisionFunc funcOnCollisionEnter;
	CallbackOnCollisionFunc funcOnCollisionStay;
	CallbackOnCollisionFunc funcOnCollisionExit;

	void InitCallbackFunc();

public:
	Collider();

	hft::HFFLOAT3 GetOffset() const { return offset; }
	hft::HFFLOAT3 GetSize() const { return size; }
	bool GetIsTrigger() const { return isTrigger; }

	void OnCollisionEnter(Collider* _p_collider);
	void OnCollisionStay(Collider* _p_collider);
	void OnCollisionExit(Collider* _p_collider);
};

