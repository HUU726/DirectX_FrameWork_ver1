#pragma once
#include"Enemy.h"


class BiteEnemy : public CEnemy
{
private:
	SpriteAnimator* p_spriteAnimator;
	int e_direction;	// このオブジェクトの方向を表す変数(0:右 1:上 2:左 3:下)
	
public:
	BiteEnemy(const float&, const float&);	// 指定された座標にオブジェクトを作成,方向の初期化
	~BiteEnemy();				// 解放処理

	void Init() override;		// コンポーネント取得
	void Update() override;		// 更新処理

	// ローテーション
	void Rotation();

	// 当たり判定
	void OnCollisionEnter(Collider* _p_collider) override;

	// 状態毎の処理をする関数
	void Normal_State();	// 通常関数
	void Attack_State();	// 攻撃関数
	void Spin_State();		// 回転関数
	void Dead_State();		// 死亡関数

	
	void SetDirection(const int& NewDirection) { e_direction = NewDirection; }
	int GetDirection() const { return e_direction; }
};
