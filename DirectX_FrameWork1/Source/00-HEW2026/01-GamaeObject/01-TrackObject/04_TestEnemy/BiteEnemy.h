#pragma once
#include"Enemy.h"

class BiteEnemy : public CEnemy
{
private:
	// 敵の情報
	float hitstopspead;	// HPが0になった際に止まる時間のスピード
	float hitstoptime;	// ヒットストップがかかるフレーム数
	hft::HFFLOAT3 Scale;	// 噛みつく敵の画像のサイズ
	GameObject2D object2D;	// 本体のアニメーション
	BoxCollider2D* bodyCollider;	// 本体の判定
	int MoveRotation[5] = { 3,0,1,0,2 };	// 行動ルーチン (死亡の時は[0]になる)  通常→攻撃→通常→回転
	int Move;				// 行動ルーチンで使用する変数
	int direction;		// 0:右 1:上 2:左 3:下

	// 攻撃の判定
	BoxCollider2D* AttackCollider;

	// 経過時間 
	int timer;

	// 状態別のフレーム数
	int Active[5] = { 20,30,20,20,3 }; // 死亡:20F 通常1:30F 攻撃:20F 通常2:20F 回転:3F

	// 向きに関する関数
	void AddDirection() { direction++; if (direction < 4) { direction = 0; } }
	int GetDirection() { return direction; }

	// 情報を返す
	int GetAct() { return MoveRotation[Move]; }
	int GetMove() { return Move; }
	void AddMove()
	{
		Move++; 
		if(Move > 4){ Move = 1; };
	}

	// アニメーションに関する関数
	void Normal_Animation();
	void Attack_Animation();
	void Spin_Animation();
	void Dead_Animation();
public:
	BiteEnemy();	
	~BiteEnemy();				

	void Init() override;		// 初期化処理
	void Update() override;		// 更新処理

	// パラメータの初期化
	void InitParam();

	//=================================================================
	// Update内の実行関数
	// ================================================================
	// フレーム,行動の更新
	void Bite_Update();
	// アニメーション
	void Bite_Animation();


	//===================================================================================
	// 自身のコライダーの状態を変更
	void SetIColliderActive(bool state);	// true:実行 false:非実行

	// 攻撃判定のコライダーの状態を変更
	void SetAColliderActive(bool state);	// true:実行 false:非実行
	// 攻撃判定のコライダーの位置を変更
	void SetAColliderPos();	// 向いている方向毎に位置を変更する


	/**
	* @brief	コライダー同士が衝突した際の処理
	* @param	Collider2D*	_p_col	2D用コライダーのポインタ
	*/
	void OnCollisionEnter(Collider* _p_col) override;

	// 状態毎の処理をする関数
	void Normal_Move();	// 通常関数
	void Attack_Move();	// 攻撃関数
	void Spin_Move();	// 回転関数
	void Dead_Move();	// 死亡関数

	void DeadMove() { Move = 0; }
};
