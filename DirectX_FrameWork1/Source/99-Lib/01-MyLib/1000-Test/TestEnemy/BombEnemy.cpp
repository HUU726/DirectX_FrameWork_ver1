//=============================================================================
//    BombEnemyクラス     
//=============================================================================

#include"BombEnemy.h"

#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

// 数値による状態(0:通常 1:攻撃)
#define NORMAL 0
#define ATTACK 1

// コンストラクタ
BombEnemy::BombEnemy(const float& Newposion_x, const float& Newposion_y)
{
	p_transform->position = hft::HFFLOAT3{ Newposion_x,Newposion_y,5.f };
	p_spriteAnimator = nullptr;
}

// デストラクタ
BombEnemy::~BombEnemy()
{
	// リソース解放
	delete p_spriteAnimator;
}

// 初期化処理
void BombEnemy::Init()
{
	// テクスチャ読み込み(仮置きとしてプレイヤーキャラクターのテクスチャを使用)
	GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/char01.png");
	p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(4, 3));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	// エネミー

	AddComponent<BoxCollider2D>();
}

// 更新処理
void BombEnemy::Update()
{
	// フレーム数更新
	SetFlame(GetFlame() + 1);

	// 状態に合わせたキャラクターの更新
	switch (GetState())
	{
	case NORMAL:
		Normal_State();
		break;
	case ATTACK:
		Attack_State();
		break;
	}
}