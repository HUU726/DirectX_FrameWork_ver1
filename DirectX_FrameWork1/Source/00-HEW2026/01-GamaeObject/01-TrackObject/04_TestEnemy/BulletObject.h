#pragma once

#pragma once
#include "../../../../01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"

#include "../../../../99-Lib/01-MyLib/07-Component/03-Collider/00-Collider/Collider.h"

class BoxCollider2D;

class BulletObject : public GameObject2D
{
private:
	// 自身の体の判定用のコライダー
	BoxCollider2D* bodyColl = nullptr;

	// 自身が存在できる時間
	int livetime = 0; 

	// 弾の進むスピード
	float spead = 1.f;

	// 経過時間
	int timer = 0;

	// 方向
	hft::HFFLOAT2 Iangle;

	enum State
	{
		defoult,
		blast,
	};
	State currentState;

	// 方向の情報
	void SetAngle(hft::HFFLOAT2 NewAngle) { Iangle = NewAngle; }
	hft::HFFLOAT2 GetAngle() { return Iangle; }

	// 方向の種類によって、自身の位置を加算する
	void UpdatePos();

	// マップの隅の超えるなら反対の座標を代入する
	void CheakMyPos();

public:
	BulletObject();
	void Init() override;
	void Update() override;

	void Stand();
	void Blast();

	void OnCollisionEnter(Collider* _p_col) override;
};