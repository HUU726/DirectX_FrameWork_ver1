#pragma once
#include"Enemy.h"
class BoxCollider2D;

class BiteEnemy : public CEnemy
{
private:
	int timer;		// 経過フレーム数

	// 敵の情報
	int direction;		// 本体の現在向いている方向		(0:右方向 1:上方向 2:左方向 3:下方向)
	int hitstoptime;	// ヒットストップがかかるフレーム数
	int defoulttime_1;	// 通常状態1のフレーム数
	int defoulttime_2;	// 通常状態2のフレーム数
	int attacktime;		// 攻撃状態のフレーム数
	int spinttime;		// 回転状態のフレーム数
	int deadtime;		// 死亡状態のフレーム数
	hft::HFFLOAT3 offset[4] = {};	// 攻撃マスの位置 
	int anipos;			// 次のアニメーションを再生するための変数
	int oldani;			// 前のアニメーションをストップするための変数
	int Act[4];
	bool changeState = false;	// アニメーションを一回実行するための変数
	bool startState = true;	// 始めのアニメーション

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
	BoxCollider2D* attackCollider;// 攻撃マスの判定
public:
	BiteEnemy();	
	~BiteEnemy();				

	void Init() override {};		// 初期化処理
	void Init(const int&);		// 方向で初期化
	void Update() override;		// 更新処理


	// 方向をセットまたは返す
	void SetDirection(const int& NewDirection) { direction = NewDirection; }
	int GetDirection() { return direction; }

	/**
	* @brief	コライダー同士が衝突した際の処理
	* @param	Collider2D*	_p_col	2D用コライダーのポインタ
	*/
	void OnCollisionEnter(Collider* _p_col) override {};
};
