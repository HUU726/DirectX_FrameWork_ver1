//=============================================================================
//    BiteEnemyクラス     
//=============================================================================

#include"BiteEnemy.h"

#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

// 数値による方向(0:右 1:上 2:左 3:下)
#define LIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

// 数値による状態(0:通常 1:攻撃 2:回転 3:死亡)
#define NORMAL 0
#define ATTACK 1
#define SPIN 2
#define DEAD 3

// コンストラクタ
BiteEnemy::BiteEnemy(const float& Newposion_x, const float& Newposion_y)
{
	p_transform->position = hft::HFFLOAT3{ Newposion_x,Newposion_y,5.f };
	p_spriteAnimator = nullptr;
	SetDirection(LIGHT);
}


// デストラクタ
BiteEnemy::~BiteEnemy()
{
	// リソース解放
	delete p_spriteAnimator;
}

// 初期化処理
void BiteEnemy::Init()
{
	// テクスチャ読み込み
	GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/char01.png");
	p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(4, 3));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	// エネミー(仮置きとしてプレイヤーキャラクターのテクスチャを使用)
	// キャラのテクスチャ
	// 右向き
	{
		// 右向き状態を3つのセルでループさせる
		SpriteAnimation anim(div, { 1,0 }, 2);
		anim.SetID(LIGHT);
		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim.SetPriority(LIGHT);
		anim.InActive();
		float flame = 60;

		for (int i = 0; i < 3; i++)
		{
			anim.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim);
	}
	// 上向き
	{
		// 上向き状態を3つのセルでループさせる
		SpriteAnimation anim(div, { 4,0 }, 2);
		anim.SetID(UP);
		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim.SetPriority(UP);
		anim.InActive();
		float flame = 60;

		for (int i = 0; i < 3; i++)
		{
			anim.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim);
	}
	// 左向き
	{
		// 左向き状態を3つのセルでループさせる
		SpriteAnimation anim(div, { 2,0 }, 2);
		anim.SetID(LEFT);
		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim.SetPriority(LEFT);
		anim.InActive();
		float flame = 60;

		for (int i = 0; i < 3; i++)
		{
			anim.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim);
	}
	// 下向き
	{
		// 下向き状態を3つのセルでループさせる
		SpriteAnimation anim(div, { 0,0 }, 2);
		anim.SetID(DOWN);
		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim.SetPriority(DOWN);
		anim.InActive();
		float flame = 60;

		for (int i = 0; i < 3; i++)
		{
			anim.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim);
	}


	AddComponent<BoxCollider2D>();
}

// 更新処理
void BiteEnemy::Update()
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
	case SPIN:
		Spin_State();
		break;
	case DEAD:
		Dead_State();
		break;
	}
}

// 状態毎の処理関数===============================================================
// 通常関数
void BiteEnemy::Normal_State()
{
	// アニメーション実行

}

// 攻撃関数
void BiteEnemy::Attack_State()
{
	
}

// 回転関数
void BiteEnemy::Spin_State()
{
	

}

// 死亡関数
void BiteEnemy::Dead_State()
{
	// 一定時間後に消去

	delete this;
}

// ローテーション(0～29:通常 30～49:攻撃 50～69:通常 70～72:回転)--------------------------------------------
void BiteEnemy::Rotation()
{
	// 自身が死亡状態ではない
	if (GetState() == DEAD) { return; }
	// フレーム数を取得
	float NowFlame = GetFlame();
	// フレーム合計
	float MaxFlame = 72;

	if (0 <= NowFlame && NowFlame <= 29) { SetState(0); }
	if (30 <= NowFlame && NowFlame <= 49) { SetState(1); }
	if (50 <= NowFlame && NowFlame <= 69) { SetState(0); }
	if (70 <= NowFlame && NowFlame <= 72) { SetState(2); }

	// 現在のフレーム数が行動の合計を超える時,0フレーム目に戻す
	if (NowFlame >= MaxFlame)
	{
		SetFlame(0);
	}
}

// 当たり判定-------------------------------
void BiteEnemy::OnCollisionEnter(Collider* _p_Collider)
{
	// 名前は相談
	if (_p_Collider->GetGameObject()->GetName() == "爆弾" || _p_Collider->GetGameObject()->GetName() == "連結" || _p_Collider->GetGameObject()->GetName() == "棘")
	{
		// ヒットストップ(オブジェクトのアニメーションを止める)
		GetComponent<BoxCollider2D>()->SetIsActive(false);	// 当たり判定を消す
		p_spriteAnimator->Stop(p_spriteAnimator->GetGameObject()->GetID());		// IDの動きの状態で止める
		SetState(DEAD);		// 状態を"死亡状態"に移行
	}
}
