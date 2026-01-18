#pragma once
#include "Enemy.h"

#include "../../../../99-Lib/01-MyLib/07-Component/03-Collider/00-Collider/Collider.h"

class BoxCollider2D;

class BomEnemy : public CEnemy
{
private:
	//自身の体の判定用のコライダー
	BoxCollider2D* bodyColl = nullptr;

	// 弾が消えてからの待機時間
	int waittimer = 30;

	// 経過時間
	int timer = 0;

	enum State
	{
		Defoult,
		shotting,
		dead,
	};
	State currentState;



	// 弾オブジェクト
	// BulletObject* bullet;

public:
	void Init() override;
	void Update() override;

	void Defoult();
	void Shotting();
	void Dead();

	void OnCollisionEnter(Collider* _p_col) override;
};
