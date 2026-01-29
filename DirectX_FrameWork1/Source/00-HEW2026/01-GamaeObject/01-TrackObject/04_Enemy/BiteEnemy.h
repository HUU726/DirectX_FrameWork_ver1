#pragma once
#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include"Enemy.h"

class BoxCollider2D;

// 攻撃判定のクラス
class AttackMass : public GameObject2D
{
private:
	bool Fg;						// trueなら当たり判定と描写をアクティブに、falseなら当たり判定と描写を非アクティブに
	int direction;					// 噛みつく敵と同じ仕様の変数
	hft::HFFLOAT3 acceptPos;		// 受け取る座標
public:
	void Init() override;
	void Update() override;

	void SetFg(const bool& NewFg) { Fg = NewFg; }							// Fgをセット 
	bool GetFg() { return Fg; }												// Fgを返す

	void SendPos(const hft::HFFLOAT3 NewPos) { acceptPos = NewPos; }		// 座標を送る用
	hft::HFFLOAT3 ReturnPos() { return p_transform->position; };			// 更新された座標を返す用

	void SendDir(const int& NewDir) { direction = NewDir; }					// 方向を送る用
	void UpdatePos();														// 方向による当たり判定のずらし	

	void MassFrash();														// マスを光らす関数
	void OnCollisionEnter(Collider* _p_col) override;
};

// 噛みつく敵(本体と攻撃判定でタグを変えるため)// 変えないと攻撃判定で爆弾を作動させたりしてしまう
class BiteEnemy : public CEnemy
{
private:
	int timer;		// 経過フレーム数
	
	// 敵の情報
	int direction;		// 本体の現在向いている方向		(0:右方向 1:上方向 2:左方向 3:下方向)
	int attackCreate;	// 攻撃判定を出すタイミング
	int defoulttime_1;	// 通常状態1のフレーム数
	int defoulttime_2;	// 通常状態2のフレーム数
	int attacktime;		// 攻撃状態のフレーム数
	int spinttime;		// 回転状態のフレーム数
	int deadtime;		// 死亡状態のフレーム数
	int anipos;			// 次のアニメーションを再生するための変数
	int oldani;			// 前のアニメーションをストップするための変数
	int Act[4];
	bool changeTrigger;	// アニメーションを一回実行するための変数
	bool startTrigger;	// 始めのアニメーション

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

	AttackMass* attackCollider;		// 攻撃の判定
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
	void OnCollisionEnter(Collider* _p_col) override;
};