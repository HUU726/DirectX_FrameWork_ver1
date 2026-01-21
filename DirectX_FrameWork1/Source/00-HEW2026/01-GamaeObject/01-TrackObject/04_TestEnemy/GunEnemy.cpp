#include"GunEnemy.h"
#include"GunEnemyParam.h"
#include"../../../../01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include"../../../../01-MyLib/08-Scene/01-Scenes/TitleScene.h"

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

//	本体のタグは"Enemy"

class ObjectManager;

GunEnemy::GunEnemy()
{
	
}

//====================================================================================================
//Init
//====================================================================================================
void GunEnemy::Init(const int & direction)
{
	// タイマーの初期化
	timer = 0;

	// パラメータ初期化
	{
		currentState = State::defoult;			// 状態をデフォルトに
		tag = GunEnemyParam::tag;				// タグを付ける:"Enemy"
		if (0 <= direction && direction < 4)SetDirection(direction);	// 方向の初期化
		else SetDirection(0);
		waittimer = GunEnemyParam::waittimer;
		shot = 0;


		// 位置の設定
		{
			p_transform->scale = GunEnemyParam::scale;
			p_transform->position = GunEnemyParam::position;
		}
	}
	
	// レンダラーの設定
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(GunEnemyParam::biteenemyTexName);

	//アニメーターの設定
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(8, 8));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	//animationの設定 
	{
		float flamecount = 0;
		// 右向き
		{
			flamecount = 12;
			// defoultのアニメーション
			SpriteAnimation anim1(div, { 0,0 }, flamecount);
			anim1.InActive();
			anim1.SetID(0);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim1.GetCellRef(i).flame = flamecount;
			}
			p_spriteAnimator->AddAnimation(anim1);

			flamecount = 6;
			// shottingのアニメーション
			SpriteAnimation anim2(div, { 5,1 }, flamecount);
			anim2.InActive();
			anim2.SetID(1);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim2.GetCellRef(i).flame = flamecount;
			}
			p_spriteAnimator->AddAnimation(anim2);
		}

		// 上向き
		{
			flamecount = 12;
			// defoultのアニメーション
			SpriteAnimation anim1(div, { 0,3 }, flamecount);
			anim1.InActive();
			anim1.SetID(2);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim1.GetCellRef(i).flame = flamecount;
			}
			p_spriteAnimator->AddAnimation(anim1);

			flamecount = 6;
			// shottingのアニメーション
			SpriteAnimation anim2(div, { 5,6 }, flamecount);
			anim2.InActive();
			anim2.SetID(3);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim2.GetCellRef(i).flame = flamecount;
			}
			p_spriteAnimator->AddAnimation(anim2);
		}

		// 左向き
		{
			flamecount = 12;
			// defoultのアニメーション
			SpriteAnimation anim1(div, { 0,0 }, flamecount);
			anim1.InActive();
			anim1.SetID(4);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim1.GetCellRef(i).flame = flamecount;
			}
			p_spriteAnimator->AddAnimation(anim1);

			flamecount = 6;
			// shottingのアニメーション
			SpriteAnimation anim2(div, { 5,1 }, flamecount);
			anim2.InActive();
			anim2.SetID(5);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim2.GetCellRef(i).flame = flamecount;
			}
			p_spriteAnimator->AddAnimation(anim2);
		}

		// 下向き
		{
			flamecount = 12;
			// defoultのアニメーション
			SpriteAnimation anim1(div, { 4,1 }, flamecount);
			anim1.InActive();
			anim1.SetID(6);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim1.GetCellRef(i).flame = flamecount;
			}
			p_spriteAnimator->AddAnimation(anim1);

			flamecount = 6;
			// shottingのアニメーション
			SpriteAnimation anim2(div, { 7,6 }, flamecount);
			anim2.InActive();
			anim2.SetID(7);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim2.GetCellRef(i).flame = flamecount;
			}
			p_spriteAnimator->AddAnimation(anim2);
		}

		flamecount = 5;
		// deadのアニメーション
		SpriteAnimation anim3(div, { 4,4 }, flamecount);
		anim3.Active();
		anim3.SetID(8);
		anim3.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim3.SetPriority(0);
		for (int i = 0; i < flamecount; i++)
		{
			anim3.GetCellRef(i).flame = flamecount;
		}
		p_spriteAnimator->AddAnimation(anim3);
	}
	

	// 当たり判定初期化
	{
		bodyColl = AddComponent<BoxCollider2D>();
		bodyColl->SetIsActive(true);
	}
	std::cout << "GunEnemyパラメータ完了\n";

	// 弾オブジェクト初期化
	
	bullet = Create<BulletObject>();
	bullet->Init(GetDirection());
	bullet->SetOwner(this);
}

//============================================================================================
//Update
//============================================================================================
void GunEnemy::Update()
{
	
	if (bullet && bullet->GetBulletActive() == true)
	{
		bullet->Update();
	}

	switch (currentState)
	{
	case State::defoult:
		Defoult();
		break;
	case State::shotting:
		Shotting();
		break;
	case State::dead:
		Dead();
		break;
	default:
		break;
	}
	
}


//===============================================================================
// 弾が存在しないとき、待ち時間を超えるとshottingへ移行する
//===============================================================================
void GunEnemy::Defoult()
{
	GetComponent<SpriteAnimator>()->Play(GetDirection() * 2);
	if (!bullet->GetBulletActive())
	{
		timer++;
		if (waittimer < timer)
		{
			timer = 0;
			currentState = GunEnemy::shotting;
		}
	}
	std::cout << "デフォルト\n";
}

//===============================================================================
// アニメーションを再生し、定められたフレームに弾オブジェクトを生成する
//===============================================================================
void GunEnemy::Shotting()
{
	if (!bullet)return;
	bullet->SetOwner(this);
	bullet->SetPos(p_transform->position);

	/*
	timer++;
	std::cout << "シューティング\n";
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 2 + 1);
	GetComponent<SpriteAnimator>()->Play(GetDirection() * 2);
	if (timer > 11)
	{
		timer = 0;
		currentState = State::defoult; 
		bullet->SetPos(p_transform->position);
		bullet->SetIsActive(true); // 弾オブジェクトをアクティブに
		bullet->SetBulletActive(true);
		std::cout << "弾オブジェクト発射!!\n";
		GetComponent<SpriteAnimator>()->Stop(GetDirection() * 2 + 1);
	}*/
}

void GunEnemy::Dead()
{
	// 当たり判定の停止
	bodyColl->SetIsActive(false);
	// 弾オブジェクトの停止
	
	bullet->SetBulletActive(false);
	bullet->SetIsActive(false);

	// エネミー総数の減少
	CEnemy::DownEnemyCount();
	// 死亡アニメーションを再生する
	GetComponent<SpriteAnimator>()->Play(8);

	// アニメーションが終わり次第、オブジェクトの機能を停止する
	GetComponent<GameObject>()->SetIsActive(false);
}

void GunEnemy::OnCollisionEnter(Collider* _p_col)
{
	// 対象のオブジェクトと接触した際、Deadへ移行
	GameObject* col = _p_col->GetGameObject();

	if (col->GetTag() == "Object")
	{
		// deadへ
		currentState = GunEnemy::dead;
	}
}