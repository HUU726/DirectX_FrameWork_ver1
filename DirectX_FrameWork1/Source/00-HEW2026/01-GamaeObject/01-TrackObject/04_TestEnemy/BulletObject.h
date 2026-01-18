#pragma once

#include "../../../../01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"
#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/03-Collider/00-Collider/Collider.h"

class BoxCollider2D;

class BulletObject : public GameObject2D
{
private:
	// 自身の体の判定用のコライダー
	BoxCollider2D* bodyColler = nullptr;

	// アニメーション用
	GameObject2D bodyObj;

	// 自身が存在できる時間
	int livetime = 60; 

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
	void SetAngle(const hft::HFFLOAT2& NewAngle) { Iangle = NewAngle; }
	hft::HFFLOAT2 GetAngle() { return Iangle; }

	// Angleから方向の情報をDirectionへ
	int direction;	// 0:右 1:上 2:左 3:下
	void SetDirection(const int& NewDirection) { direction = NewDirection; }
	int GetDirection() { return direction; }

	// 方向の種類によって、自身の位置を加算する
	void UpdatePos();

	// マップの隅の超えるなら反対の座標を代入する
	void CheakMyPos();

public:
	BulletObject(const hft::HFFLOAT3& NewPosition, const hft::HFFLOAT2& NewAngle); // 座標、方向を初期化
	void Init() override;
	void Update() override;

	void Defoult();
	void Blast();

	void OnCollisionEnter(Collider* _p_col) override;
};