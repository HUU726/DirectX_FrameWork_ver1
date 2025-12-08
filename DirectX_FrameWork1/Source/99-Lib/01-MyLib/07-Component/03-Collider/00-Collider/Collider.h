#pragma once

#include "../../00-Component/Component.h"

#include "../../../998-FH_Types/HF_FLOAT.h"
#include <functional>

//コールバック用関数オブジェクト型定義
class Collider;
typedef std::function<void(Collider*)> CallbackOnCollisionFunc;



class Collider : public Component
{
protected:
	hft::HFFLOAT3 offset;
	hft::HFFLOAT3 size;
	bool isTrigger;

	std::vector<Collider*> curHitColliders;	//現フレーム、ヒットしたコライダ一覧
	std::vector<Collider*> preHitColliders;	//前フレーム、ヒットしたコライダ一覧
	CallbackOnCollisionFunc funcOnCollisionEnter;	//CollisionEnter用関数オブジェクト
	CallbackOnCollisionFunc funcOnCollisionStay;	//CollisionStay用関数オブジェクト
	CallbackOnCollisionFunc funcOnCollisionExit;	//CollisionExit用関数オブジェクト

	void InitCallbackFunc();

public:
	Collider();

	hft::HFFLOAT3 GetOffset() const { return offset; }
	virtual hft::HFFLOAT3 GetSize() const { return size; }
	bool GetIsTrigger() const { return isTrigger; }

	void SetOffset(const hft::HFFLOAT3& _offset) { offset = _offset; }
	void SetSize(const hft::HFFLOAT3& _size) { size = _size; }
	void SetIsTrigger(bool _is) { isTrigger = _is; }

	void AddCurHitCollider(Collider* _p_collider);
	void SwapHitColliders();
	void CheckHitColliders();

	void OnCollisionEnter(Collider* _p_collider);
	void OnCollisionStay(Collider* _p_collider);
	void OnCollisionExit(Collider* _p_collider);
};

