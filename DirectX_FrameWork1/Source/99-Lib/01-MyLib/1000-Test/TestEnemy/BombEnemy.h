#pragma once
#include"Enemy.h"


class BombEnemy : public CEnemy
{
private:
	SpriteAnimator* p_spriteAnimator;

public:
	BombEnemy(const float&, const float&);	// 指定された座標にオブジェクトを作成
	~BombEnemy();				// 解放処理

	void Init() override;		// コンポーネント取得
	void Update() override;		// 更新処理

	// 当たり判定
	void OnCollisionEnter(Collider* _p_collider) override;

	// 状態毎の処理をする関数
	void Normal_State();	// 通常関数
	void Attack_State();	// 攻撃関数
};