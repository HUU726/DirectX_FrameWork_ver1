#pragma once
#include"Enemy.h"

class BiteEnemy : public CEnemy
{
private:
	int timer;		// 経過フレーム数

	// 敵の情報
	int direction;		// 本体の向いている方向		(0:右方向 1:上方向 2:左方向 3:下方向)
	int hitstoptime;	// ヒットストップがかかるフレーム数
	int defoulttime_1;	// 通常状態1のフレーム数
	int defoulttime_2;	// 通常状態2のフレーム数
	int attacktime;		// 攻撃状態のフレーム数
	int spinttime;		// 回転状態のフレーム数
	int deadtime;		// 死亡状態のフレーム数
	hft::HFFLOAT3 offset[4] = {};


	enum State
	{
		defoult1,
		defoult2,
		attack,
		spin,
		dead
	};
	State currentState;

	void Defoult1();
	void Defoult2();
	void Attack();
	void Spin();
	void Dead();


	GameObject2D object2D;	// 本体のアニメーション
	BoxCollider2D* bodyCollider;	// 本体の判定
	BoxCollider2D* attackCollider;	// 攻撃の判定
public:
	BiteEnemy();	
	~BiteEnemy();				

	void Init() override;		// 初期化処理
	void Update() override;		// 更新処理


	// 方向をセットまたは返す
	void SetDirection(const int& NewDirection) { direction = NewDirection; }
	int GetDirection() { return direction; }

	/**
	* @brief	コライダー同士が衝突した際の処理
	* @param	Collider2D*	_p_col	2D用コライダーのポインタ
	*/
	void OnCollisionEnter(Collider* _p_col) override;
};
