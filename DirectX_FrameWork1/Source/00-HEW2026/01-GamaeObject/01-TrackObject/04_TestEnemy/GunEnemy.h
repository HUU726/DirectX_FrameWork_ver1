#pragma once
#include "Enemy.h"
#include"BulletObject.h"
#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

class GunEnemy : public CEnemy
{
private:
	// 自身の体の判定用のコライダー
	BoxCollider2D* bodyColl = nullptr;

	// 弾が消えてからの待機時間
	int waittimer;

	// 経過時間
	int timer;

	// 弾オブジェクトを作成するフレーム数
	int shot;

	enum State
	{
		defoult,
		shotting,
		dead,
	};
	State currentState;

	// 方向 /*(-1,0):左向き (0,1):上向き (1,0)右向き (0,-1):下向き*/
	void SetAngle(hft::HFFLOAT2 NewAngle) { angle = NewAngle; }
	hft::HFFLOAT2 GetAngle() { return angle; }

	// 弾オブジェクト
	BulletObject bullet;

public:
	GunEnemy();
	void Init() override;
	void Update() override;

	void Defoult();
	void Shotting();
	void Dead();

	void OnCollisionEnter(Collider* _p_col) override;
};
