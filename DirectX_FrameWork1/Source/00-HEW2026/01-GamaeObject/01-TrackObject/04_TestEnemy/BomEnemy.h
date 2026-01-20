#pragma once

#include "Enemy.h"

#include "../../../../99-Lib/01-MyLib/07-Component/03-Collider/00-Collider/Collider.h"

enum BomState

{

	stand,

	blastWait,

	blast,

	dead,

};

//検査用の当たり判定の親は自身につけ、攻撃判定は普通のゲームオブジェクト


class BoxCollider2D;

class BomEnemy : public CEnemy

{

private:

	//自身の体の判定用のコライダー

	BoxCollider2D* bodyColl = nullptr;

	//自身の爆発範囲検知用のゲームオブジェクト

	GameObject2D* searchRenderer = nullptr;		//画像表示用

	BoxCollider2D* searchColl = nullptr;		//当たり判定用

	//自身の爆発用のゲームオブジェクト

	BoxCollider2D* bomColl = nullptr;

	//自身の起爆時間

	int blastWaitTime = 20;

	int blastTime = 40;

	int timer = 0;

	BomState currentState = BomState::stand;

public:

	void Init() override;

	void Update() override;

	//通常状態の処理

	void Stand();

	//爆発前の処理

	void BlastWait();

	//爆発時の処理

	void Blast();

	//爆発後の処理

	void Dead();

	BomState GetState() { return currentState; }

	void OnCollisionEnter(Collider* _p_col) override;

	void OnCollisionExit(Collider* _p_col) override;

	void OnCollisionStay(Collider* _p_col) override;

};
