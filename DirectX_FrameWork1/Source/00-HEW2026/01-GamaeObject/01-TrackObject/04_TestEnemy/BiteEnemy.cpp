#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#include"BiteEnemy.h"
#include"BiteEnemyParam.h"

BiteEnemy::BiteEnemy()
{
	
}

BiteEnemy::~BiteEnemy()
{

}

// 初期化=============================================================
void BiteEnemy::Init()
{
	timer = 0;	// タイマーの初期化
	hitstoptime = BiteEnemyParam::hitstoptime;	// ヒットストップ時間
	currentState = BiteEnemy::defoult1;
	defoulttime_1 = BiteEnemyParam::defoult1;
	defoulttime_2 = BiteEnemyParam::defoult2;
	attacktime = BiteEnemyParam::attack;
	spinttime = BiteEnemyParam::spin;
	deadtime = BiteEnemyParam::dead;
	for (int i = 0; i < 4; i++)
	{
		offset[i] = BiteEnemyParam::offset[i];
	}

	// 位置の設定
	{
		p_transform->scale = BiteEnemyParam::scale;
		p_transform->position = BiteEnemyParam::position;
	}

	// レンダラーの設定
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(BiteEnemyParam::BiteEnemyTexName);

	//アニメーターの設定
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(2, 3));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	//animationの設定
	{
		// 通常状態のアニメーション
		SpriteAnimation anim1(div, { 0,0 }, 6);
		anim1.Active();
		anim1.SetID(0);
		anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim1.SetPriority(0);
		float flame = 10;
		for (int i = 0; i < 6; i++)
		{
			anim1.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim1);

		// 攻撃状態のアニメーション
		SpriteAnimation anim2(div, { 0,0 }, 6);
		anim2.Active();
		anim2.SetID(1);
		anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim2.SetPriority(0);
		flame = 10;
		for (int i = 0; i < 6; i++)
		{
			anim2.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim2);

		// 回転状態のアニメーション
		SpriteAnimation anim3(div, { 0,0 }, 6);
		anim3.Active();
		anim3.SetID(2);
		anim3.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim3.SetPriority(0);
		flame = 10;
		for (int i = 0; i < 6; i++)
		{
			anim3.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim3);

		// 死亡状態のアニメーション
		SpriteAnimation anim4(div, { 0,0 }, 6);
		anim4.Active();
		anim4.SetID(3);
		anim4.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim4.SetPriority(0);
		flame = 10;
		for (int i = 0; i < 6; i++)
		{
			anim4.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim4);
	}
	
	// 本体のコライダーの設定
	bodyCollider = AddComponent<BoxCollider2D>();
	bodyCollider->SetIsActive(true);

	//攻撃のコライダーの設定
	attackCollider = AddComponent<BoxCollider2D>();
	attackCollider->SetOffset({ -50.f,0.0f,0.0f });
	attackCollider->SetIsActive(false);

	std::cout << "BiteEnemyパラメータ完了\n";
}

// 更新===============================================================
void BiteEnemy::Update()
{
	timer++;
	switch (currentState)
	{
	case defoult1:
		break;
	case defoult2:
		break;
	case attack:
		break;
	case spin:
		break;
	case dead:
		break;
	default:
		std::cout << "状態エラー\n";
	}
}


//==================================================================================
// 通常状態の行動
//==================================================================================
void BiteEnemy::Defoult1()
{
	GetComponent<SpriteAnimator>()->Stop(2);
	GetComponent<SpriteAnimator>()->Play(0);
	if (timer > defoulttime_1)
	{
		currentState = BiteEnemy::attack;		// 攻撃へ
		timer = 0;
	}
}

void BiteEnemy::Defoult2()
{
	GetComponent<SpriteAnimator>()->Stop(2);
	GetComponent<SpriteAnimator>()->Play(0);
	if (timer > defoulttime_2)
	{
		currentState = BiteEnemy::spin;			// 回転へ
		timer = 0;
	}
}

//==================================================================================
// 攻撃状態の行動
//==================================================================================
void BiteEnemy::Attack()
{
	attackCollider->SetOffset(offset[GetDirection()]);
	GetComponent<SpriteAnimator>()->Stop(0);
	GetComponent<SpriteAnimator>()->Play(1);
	attackCollider->SetIsActive(true);			// 当たり判定をアクティブに
	if (timer > attack)
	{
		currentState = BiteEnemy::defoult2;		// 通常状態へ
		attackCollider->SetIsActive(false);			// 当たり判定を非アクティブに
		timer = 0;
	}
}

//==================================================================================
// 回転状態の行動
//==================================================================================
void BiteEnemy::Spin()
{
	GetComponent<SpriteAnimator>()->Stop(0);
	GetComponent<SpriteAnimator>()->Play(2);
	if (timer > attack)
	{
		currentState = BiteEnemy::defoult1;		// 通常状態へ
		SetDirection(GetDirection() + 1);		// 方向変換
		if (GetDirection() <= 4) { SetDirection(0); }
		timer = 0;
	}
}

/**
*@brief	コライダー同士が衝突した際の処理
* @param	Collider2D* _p_col	2D用コライダーのポインタ
*/
void BiteEnemy::OnCollisionEnter(Collider* _p_col)
{
	// 接触相手の情報を取得
	GameObject* col = _p_col->GetGameObject();

	// タグが特定の対象であれば本体を死亡状態へ
	bool cheakHit = false;
	/*
	if (col->GetTag()=="a")
	{
		//DeadMove();			// 死亡状態へ
	}
	*/
}