#pragma once
#include"Enemy.h"

class BiteEnemy : public CEnemy
{
private:
	// 敵の情報
	float hitstopspeed;	// HPが0になった際に止まる時間のスピード
	float hitstoptime;	// ヒットストップがかかるフレーム数
	hft::HFFLOAT3 Scale;	// 噛みつく敵の画像のサイズ
	GameObject2D object2D;	// 本体のアニメーション
	int Move[4] = { 1,2,1,3 };	// 行動ルーチン



	// 経過時間 
	int timer;

	// 状態別のフレーム数
	int Idle_flame;
	int Attack_flame;
	int Spin_flame;
	int Dead_flame;

	// 向きに関する関数
	void SetAngle(const hft::HFFLOAT2& NewAngle) { return; }
	hft::HFFLOAT2 GetAngle() { return angle; }
public:
	BiteEnemy();	
	~BiteEnemy();				

	void Init() override;		// 初期化処理
	void Update() override;		// 更新処理

	// コライダーの状態を変更
	void SetColliderActive(bool state);

	// 状態毎の処理をする関数
	void Normal_Move();	// 通常関数
	void Attack_Move();	// 攻撃関数
	void Spin_Move();	// 回転関数
	void Dead_Move();	// 死亡関数

	// ヒットストップ
	void SetDelay();

	// アニメーション
	void Normal_Animation();
	void Attack_Animation();
	void Spin_Animation();
	void Dead_Animation();
};
