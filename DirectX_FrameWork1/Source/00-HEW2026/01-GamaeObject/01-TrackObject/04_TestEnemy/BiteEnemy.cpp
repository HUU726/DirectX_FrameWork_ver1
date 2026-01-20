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
	tag = BiteEnemyParam::tag;	// 本体のタグ:Bite
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
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(8, 7));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	//animationの設定
	{
		// 右向き
		{
			// 通常状態のアニメーション
			SpriteAnimation anim1(div, { 0,0 }, 10);
			anim1.Active();
			anim1.SetID(0);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			float flame = 10;
			for (int i = 0; i < 10; i++)
			{
				anim1.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim1);

			// 攻撃状態のアニメーション
			SpriteAnimation anim2(div, { 2,4 }, 6);
			anim2.Active();
			anim2.SetID(1);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			flame = 15;
			for (int i = 0; i < 15; i++)
			{
				anim2.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim2);

			// 回転状態のアニメーション
			SpriteAnimation anim3(div, { 0,0 }, 0);
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
		}
		
		// 上向き
		{
			// 通常状態のアニメーション
			SpriteAnimation anim1(div, { 2,1 }, 10);
			anim1.Active();
			anim1.SetID(3);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			float flame = 10;
			for (int i = 0; i < 10; i++)
			{
				anim1.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim1);

			// 攻撃状態のアニメーション
			SpriteAnimation anim2(div, { 7,1 }, 6);
			anim2.Active();
			anim2.SetID(4);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			flame = 10;
			for (int i = 0; i < 12; i++)
			{
				anim2.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim2);

			// 回転状態のアニメーション
			SpriteAnimation anim3(div, { 0,0 }, 6);
			anim3.Active();
			anim3.SetID(5);
			anim3.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim3.SetPriority(0);
			flame = 10;
			for (int i = 0; i < 6; i++)
			{
				anim3.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim3);
		}

		// 左向き
		{
			// 通常状態のアニメーション
			SpriteAnimation anim1(div, { 0,0 }, 10);
			anim1.Active();
			anim1.SetID(6);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			float flame = 10;
			for (int i = 0; i < 10; i++)
			{
				anim1.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim1);

			// 攻撃状態のアニメーション
			SpriteAnimation anim2(div, { 2,4 }, 6);
			anim2.Active();
			anim2.SetID(7);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			flame = 10;
			for (int i = 0; i < 15; i++)
			{
				anim2.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim2);

			// 回転状態のアニメーション
			SpriteAnimation anim3(div, { 0,0 }, 0);
			anim3.Active();
			anim3.SetID(8);
			anim3.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim3.SetPriority(0);
			flame = 10;
			for (int i = 0; i < 6; i++)
			{
				anim3.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim3);
		}

		// 下向き
		{
			// 通常状態のアニメーション
			SpriteAnimation anim1(div, { 2,1 }, 10);
			anim1.Active();
			anim1.SetID(9);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			float flame = 10;
			for (int i = 0; i < 10; i++)
			{
				anim1.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim1);

			// 攻撃状態のアニメーション
			SpriteAnimation anim2(div, { 3,5 }, 6);
			anim2.Active();
			anim2.SetID(10);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			flame = 10;
			for (int i = 0; i < 12; i++)
			{
				anim2.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim2);

			// 回転状態のアニメーション
			SpriteAnimation anim3(div, { 0,0 }, 6);
			anim3.Active();
			anim3.SetID(11);
			anim3.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim3.SetPriority(0);
			flame = 10;
			for (int i = 0; i < 6; i++)
			{
				anim3.GetCellRef(i).flame = flame;
			}
			p_spriteAnimator->AddAnimation(anim3);
		}

		// 死亡状態のアニメーション
		SpriteAnimation anim4(div, { 6,3 }, 4);
		anim4.Active();
		anim4.SetID(10);
		anim4.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim4.SetPriority(0);
		float flame = 10;
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
	attackCollider.SetTag("Enemy");
	attackCollider.col()->SetSize(bodyCollider->GetSize());
	attackCollider.col()->SetOffset({ 50.f,0.0f,0.0f });
	attackCollider.col()->SetIsActive(false);

	std::cout << "BiteEnemyパラメータ完了\n";
}

// 更新===============================================================
void BiteEnemy::Update()
{
	timer++;
	switch (currentState)
	{
	case defoult1:
		Defoult1();
		break;
	case defoult2:
		Defoult2();
		break;
	case attack:
		Attack();
		break;
	case spin:
		Spin();
		break;
	case dead:
		Dead();
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
	std::cout << "通常状態1実行中\n";
	std::cout << "現在の方向:" << GetDirection() << "\n";
	GetComponent<SpriteAnimator>()->Play(GetDirection() * 3);
	if (timer > defoulttime_1)
	{
		currentState = BiteEnemy::attack;		// 攻撃へ
		timer = 0;
	}
}

void BiteEnemy::Defoult2()
{
	std::cout << "通常状態2実行中\n";
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3 + 1);
	GetComponent<SpriteAnimator>()->Play(GetDirection() * 3);
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
	std::cout << "攻撃状態実行中\n";
	attackCollider.col()->SetOffset(offset[GetDirection()]);
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3);
	GetComponent<SpriteAnimator>()->Play(GetDirection() * 3 + 1);
	attackCollider.col()->SetIsActive(true);			// 当たり判定をアクティブに
	if (timer > attacktime)
	{
		currentState = BiteEnemy::defoult2;		// 通常状態へ
		attackCollider.col()->SetIsActive(false);			// 当たり判定を非アクティブに
		timer = 0;
	}
}

//==================================================================================
// 回転状態の行動
//==================================================================================
void BiteEnemy::Spin()
{
	std::cout << "回転状態実行中\n";
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3);
	GetComponent<SpriteAnimator>()->Play(GetDirection() * 3 + 2);
	if (timer > spinttime)
	{
		GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3 + 2);
		currentState = BiteEnemy::defoult1;		// 通常状態へ
		SetDirection(GetDirection() + 1);		// 方向変換
		if (GetDirection() >= 4) { SetDirection(0); }
		timer = 0;
	}
}


//==================================================================================
// 状態の行動
//==================================================================================
void BiteEnemy::Dead()
{
	// 当たり判定停止
	bodyCollider->SetIsActive(false);
	attackCollider.col()->SetIsActive(false);
	// アニメーション
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3);
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3 + 1);
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3 + 2);
	GetComponent<SpriteAnimator>()->Play(10);
	if (timer > dead)
	{
		std::cout << "BiteEnemy機能停止\n";
		SetIsActive(false);
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

	if (_p_col == bodyCollider)
	{
		// 本体がヒット
		if (col->GetTag() == "Object")
		{
			timer = 0;
			std::cout << "BIteEnemy本体にヒット\n";
			currentState = BiteEnemy::dead;
		}
	}
	else if (_p_col == attackCollider.col())
	{
		// 攻撃がヒット
		std::cout << "BiteEnemyの攻撃がヒット\n";
		return;
	}
}