#pragma once
#include "Enemy.h"

#include "../../../../99-Lib/01-MyLib/07-Component/03-Collider/00-Collider/Collider.h"

class BoxCollider2D;

class BomEnemy : public CEnemy
{
private:
	//自身の体の判定用のコライダー
	BoxCollider2D* bodyColl = nullptr;

	//自身の爆発範囲検知用のコライダー
	BoxCollider2D* searchColl = nullptr;
	
	//自身の爆発用のコライダー
	BoxCollider2D* bomColl = nullptr;


	//自身の起爆時間
	int blastWaitTime = 40;
	int blastTime     = 60;

	int timer = 0;

	enum State
	{
		stand,
		blastWait,
		blast,
		dead,
	};
	State currentState;

	bool isBlast = false;

public:
	void Init() override;
	void Update() override;

	void Stand();
	void BlastWait();
	void Blast();
	void Dead();

	void OnCollisionEnter(Collider* _p_col) override;
	void OnCollisionExit(Collider* _p_col) override;
	void OnCollisionStay(Collider* _p_col) override;
};