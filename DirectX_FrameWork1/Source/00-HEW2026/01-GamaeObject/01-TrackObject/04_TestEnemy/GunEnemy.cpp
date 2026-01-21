//	本体のタグは"Enemy"

#include"GunEnemy.h"
#include"GunEnemyParam.h"
#include"../../../../01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

GunEnemy::GunEnemy()
{
	
}

//====================================================================================================
//Init
//====================================================================================================
void GunEnemy::Init(BaseMap* map)
{
	// パラメータ初期化
	{
		//マップ上どのマスにいるか設定
		//SetLineIndex({1.f, 1.f});
		currentState = State::defoult;

		tag = GunEnemyParam::tag;

		// 向きの調整
		//hft::HFFLOAT2 AGL = angle;
		hft::HFFLOAT2 AGL = { 1,0 };
		SetAngle(AGL);
		const hft::HFFLOAT2 RIGHTANGLE = { 1,0 };
		const hft::HFFLOAT2 UPANGLE = { 0,1 };
		const hft::HFFLOAT2 LEFTANGLE = { -1,0 };
		const hft::HFFLOAT2 DOWNANGLE = { 0,-1 };

		hft::HFFLOAT2 NewAngle = GetAngle();
		if (NewAngle.x == RIGHTANGLE.x && NewAngle.y == RIGHTANGLE.y) { SetDirection(RIGHT); }
		else if (NewAngle.x == UPANGLE.x && NewAngle.y == UPANGLE.y) { SetDirection(UP); }
		else if (NewAngle.x == LEFTANGLE.x && NewAngle.y == LEFTANGLE.y) { SetDirection(LEFT); }
		else if (NewAngle.x == DOWNANGLE.x && NewAngle.y == DOWNANGLE.y) { SetDirection(DOWN); }
		else { std::cout << "エラー\n"; }
		// タイマーの初期化
		timer = 0;

		// 位置の設定
		{
			p_transform->scale = GunEnemyParam::scale;
			p_transform->position = GunEnemyParam::position;
		}
	}

	// レンダラーの設定
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(GunEnemyParam::biteenemyTexName);

	//アニメーターの設定
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(2, 3));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	//animationの設定
	// 右向き
	{
		// defoultのアニメーション
		SpriteAnimation anim1(div, { 0,0 }, 12);
		anim1.Active();
		anim1.SetID(0);
		anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim1.SetPriority(0);
		float flame = 12;
		for (int i = 0; i < 6; i++)
		{
			anim1.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim1);

		// shottingのアニメーション
		SpriteAnimation anim2(div, { 5,1 },6 );
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
	}

	// 上向き
	{
		// defoultのアニメーション
		SpriteAnimation anim1(div, { 0,3 }, 12);
		anim1.Active();
		anim1.SetID(2);
		anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim1.SetPriority(0);
		float flame = 12;
		for (int i = 0; i < 12; i++)
		{
			anim1.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim1);

		// shottingのアニメーション
		SpriteAnimation anim2(div, { 5,6 }, 6);
		anim2.Active();
		anim2.SetID(3);
		anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim2.SetPriority(0);
		flame = 13;
		for (int i = 0; i < 6; i++)
		{
			anim2.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim2);
	}

	// 左向き
	{
		// defoultのアニメーション
		SpriteAnimation anim1(div, { 0,0 }, 12);
		anim1.Active();
		anim1.SetID(4);
		anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim1.SetPriority(0);
		float flame = 12;
		for (int i = 0; i < 12; i++)
		{
			anim1.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim1);

		// shottingのアニメーション
		SpriteAnimation anim2(div, { 5,1 }, 6);
		anim2.Active();
		anim2.SetID(5);
		anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim2.SetPriority(0);
		flame = 10;
		for (int i = 0; i < 6; i++)
		{
			anim2.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim2);
	}

	// 下向き
	{
		// defoultのアニメーション
		SpriteAnimation anim1(div, { 4,1 }, 12);
		anim1.Active();
		anim1.SetID(6);
		anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim1.SetPriority(0);
		float flame = 12;
		for (int i = 0; i < 12; i++)
		{
			anim1.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim1);

		// shottingのアニメーション
		SpriteAnimation anim2(div, { 7,6 }, 6);
		anim2.Active();
		anim2.SetID(7);
		anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim2.SetPriority(0);
		flame = 13;
		for (int i = 0; i < 6; i++)
		{
			anim2.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim2);
	}

	// deadのアニメーション
	SpriteAnimation anim3(div, { 4,4 }, 5);
	anim3.Active();
	anim3.SetID(8);
	anim3.SetType(SPRITE_ANIM_TYPE::NORMAL);
	anim3.SetPriority(0);
	float flame = 12;
	for (int i = 0; i < 5; i++)
	{
		anim3.GetCellRef(i).flame = flame;
	}
	p_spriteAnimator->AddAnimation(anim3);

	// 当たり判定初期化
	{
		bodyColl = AddComponent<BoxCollider2D>();
		bodyColl->SetIsActive(true);
	}

	std::cout << "GunEnemyパラメータ完了\n";

	// 弾オブジェクト初期化
	bullet.Init(GetAngle(), map);
}

//============================================================================================
//Update
//============================================================================================
void GunEnemy::Update()
{
	if (bullet.GetBulletActive() == true)
	{
		bullet.Update();
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
	if (bullet.GetBulletActive() != true)
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
	timer++;
	std::cout << "シューティング\n";
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 2 + 1);
	GetComponent<SpriteAnimator>()->Play(GetDirection() * 2);
	if (timer > 11)
	{
		timer = 0;
		currentState = State::defoult; 
		bullet.SetPos(p_transform->position);
		bullet.SetBulletActive(true); // 弾オブジェクトをアクティブに
		std::cout << "弾オブジェクト発射!!\n";
		GetComponent<SpriteAnimator>()->Stop(GetDirection() * 2 + 1);
	}
}

void GunEnemy::Dead()
{
	// 当たり判定の停止
	bodyColl->SetIsActive(false);
	// 弾オブジェクトの停止
	
	bullet.SetBulletActive(false);
	bullet.SetIsActive(false);

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