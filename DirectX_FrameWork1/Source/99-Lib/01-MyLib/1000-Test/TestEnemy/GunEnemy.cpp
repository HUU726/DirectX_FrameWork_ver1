/*
//=============================================================================
//    GunEnemyクラス     
//=============================================================================

#include"GunEnemy.h"

#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

// 数値による方向(0:右 1:上 2:左 3:下)
#define LIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

// 数値による状態(0:通常 1:攻撃 2:死亡)
#define NORMAL 0
#define ATTACK 1
#define DEAD 2

// コンストラクタ
GunEnemy::GunEnemy(const float& Newposion_x, const float& Newposion_y,const int& NewDirection)
{
	p_transform->position = hft::HFFLOAT3{ Newposion_x,Newposion_y,5.f };
	p_spriteAnimator = nullptr;
	SetDirection(NewDirection);
	// ballet = nullptr;
}

// デストラクタ
GunEnemy::~GunEnemy()
{
	// リソース解放
	delete p_spriteAnimator;
}

// 初期化処理
void GunEnemy::Init()
{
	// テクスチャ読み込み(仮置きとしてプレイヤーキャラクターのテクスチャを使用)
	GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/char01.png");
	p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(4, 3));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	// エネミー

	AddComponent<BoxCollider2D>();
}

// 更新処理
void GunEnemy::Update()
{
	// フレーム数更新
	SetFlame(GetFlame() + 1);
	// ローテーション
	Rotation();

	// 状態に合わせたキャラクターの更新
	switch (GetState())
	{
	case NORMAL:
		Normal_State();
		break;
	case ATTACK:
		Attack_State();
		break;
	case DEAD:
		Dead_State();
		break;
	}
}

// ローテーション(0～39:通常 40～59:攻撃)--------------------------------------------
void GunEnemy::Rotation()
{
	// 自身が死亡状態ではない
	if (GetState() == DEAD) { return; }
	// フレーム数を取得
	float NowFlame = GetFlame();
	// フレーム合計
	float MaxFlame = 60;

	if (NowFlame >= MaxFlame)
	{
		SetFlame(0);
	}
	//ballet = new BalletObject;
}*/