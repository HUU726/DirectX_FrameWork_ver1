#include"GunEnemy.h"
#include"GunEnemyParam.h"
#include"../../../../01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include"../../01-TrackObject/02_ThornObject/ThormObject.h"
#include"../../01-TrackObject/03_ConnectObject/ConnectObject.h"
#include"../../01-TrackObject/04_Enemy/BombEnemy.h"
#include"../../../../01-MyLib/06-GameObject/999-GameObjectManager/GameObjectManager.h"

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

//	タグは"Gun"

// コンストラクタ
GunEnemy::GunEnemy()
{
	name = "Gun";
}

// デストラクタ
GunEnemy::~GunEnemy()
{
	if (!bullet) { delete bullet; bullet = nullptr; }
}

//====================================================================================================
// 弾を撃つ敵の初期化処理(Init)
//====================================================================================================
void GunEnemy::Init(BaseMap* _p_map, const int& direction)
{
	timer = 0;												// タイマーの初期化
	SetTag(GunEnemyParam::tag);								// タグを付ける:"Gun"
	currentState = GunEnemy::defoult;						// 状態をデフォルトに
	changeTrigger = GunEnemyParam::changeScene;				// changeSceneをfalseで初期化
	startTrigger = GunEnemyParam::startScene;				// startSceneをtrueで初期化
	anipos = GunEnemyParam::anipos;							// aniposを初期化
	oldani = GunEnemyParam::oldani;							// oldaniを初期化
	waittimer = GunEnemyParam::waittimer;					// 弾が非アクティブになってからの待機時間を初期化
	bulletcreateflame = GunEnemyParam::bulletcreateflame;	// 弾オブジェクトを生成するフレーム
	deadtime = GunEnemyParam::deadtime;						// 死亡状態にかかるフレーム

	if (0 <= direction && direction < 4)SetDirection(direction);	// 方向の初期化
	else { SetDirection(0); }

	// 位置の設定
	{
		p_transform->scale = GunEnemyParam::scale;
		p_transform->position = GunEnemyParam::position;
	}


	// レンダラーの設定
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(GunEnemyParam::gunenemyTexName);

	//アニメーターの設定
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(8, 8));
	//SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(8, 11));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	//animationの設定 
	{
		float flamecount = 0;
		float flameraito = 0;
		// 右向き
		{
			flamecount = 12;
			flameraito = 12;
			// defoultのアニメーション
			SpriteAnimation anim1(div, { 0,0 }, flamecount);
			//SpriteAnimation anim1(div, { 4,7 }, flamecount);
			anim1.InActive();
			anim1.SetID(0);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim1.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim1);

			flamecount = 6;
			flameraito = 12;
			// shottingのアニメーション
			SpriteAnimation anim2(div, { 1,5 }, flamecount);
			//SpriteAnimation anim2(div, { 5,9 }, flamecount);
			anim2.InActive();
			anim2.SetID(1);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim2.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim2);
		}

		// 上向き
		{
			flamecount = 12;
			flameraito = 12;
			// defoultのアニメーション
			SpriteAnimation anim1(div, { 0,3 }, flamecount);
			anim1.InActive();
			anim1.SetID(2);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim1.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim1);

			flamecount = 6;
			flameraito = 12;
			// shottingのアニメーション
			SpriteAnimation anim2(div, { 5,6 }, flamecount);
			anim2.InActive();
			anim2.SetID(3);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim2.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim2);
		}

		// 左向き
		{
			flamecount = 12;
			flameraito = 12;
			// defoultのアニメーション
			SpriteAnimation anim1(div, { 0,0 }, flamecount);
			anim1.InActive();
			anim1.SetID(4);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim1.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim1);

			flamecount = 6;
			flameraito = 12;
			// shottingのアニメーション
			SpriteAnimation anim2(div, { 1,5 }, flamecount);
			anim2.InActive();
			anim2.SetID(5);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim2.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim2);
		}

		// 下向き
		{
			flamecount = 12;
			flameraito = 12;
			// defoultのアニメーション
			SpriteAnimation anim1(div, { 4,1 }, flamecount);
			anim1.InActive();
			anim1.SetID(6);
			anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim1.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim1.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim1);

			flamecount = 6;
			flamecount = 12;
			// shottingのアニメーション
			SpriteAnimation anim2(div, { 7,5 }, flamecount);
			anim2.InActive();
			anim2.SetID(7);
			anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim2.SetPriority(0);
			for (int i = 0; i < flamecount; i++)
			{
				anim2.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim2);
		}

		// deadのアニメーション
		{
			// 右向き
			{
				flamecount = 5;
				flameraito = 8;
				SpriteAnimation anim3(div, { 4,4 }, flamecount);
				//SpriteAnimation anim3(div, { 0,9 }, flamecount);
				anim3.InActive();
				anim3.SetID(8);
				anim3.SetType(SPRITE_ANIM_TYPE::NORMAL);
				anim3.SetPriority(0);
				for (int i = 0; i < flamecount; i++)
				{
					anim3.GetCellRef(i).flame = flameraito;
				}
				p_spriteAnimator->AddAnimation(anim3);
			}
			// 左向き
			{
				/*
				flamecount = 5;
				flameraito = 8;
				SpriteAnimation anim3(div, { 4,4 }, flamecount);
				anim3.InActive();
				anim3.SetID(9);
				anim3.SetType(SPRITE_ANIM_TYPE::NORMAL);
				anim3.SetPriority(0);
				for (int i = 0; i < flamecount; i++)
				{
					anim3.GetCellRef(i).flame = flameraito;
				}
				p_spriteAnimator->AddAnimation(anim3);
				*/
			}
		}
	}

	int dir = GetDirection();
	anipos = dir * 2;
	p_spriteAnimator->Play(anipos);

	// 当たり判定初期化
	auto bodyColl = AddComponent<BoxCollider2D>();
	bodyColl->Init();
	bodyColl->SetSize(p_transform->scale);					// 本体のサイズ分当たり判定をとる

	// マップの情報
	// 弾オブジェクト初期化
	bullet = new BulletObject;					// 弾オブジェクト生成
	bullet->Init(_p_map, GetDirection());		//	弾オブジェクトの初期化(マップの情報,方向)
}

//===============================================================================================
// 弾撃つ敵の更新処理(Update)
//===============================================================================================
void GunEnemy::Update()
{
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

//===============================================================================================
// 通常状態の処理
//===============================================================================================
void GunEnemy::Defoult()
{											// タイマー更新
	// 方向を取得
	int dir = GetDirection();
	anipos = dir * 2;									// 方向から再生するIDを決定する
	
	// ゲームが始まった際,一度だけ通る
	if (startTrigger == true)
	{
		startTrigger = false;
		life = false;
		GetComponent<SpriteAnimator>()->Play(anipos);	// 最初のアニメーションを再生
	}

	// この状態中、一度だけ通るコード
	if (changeTrigger == true)
	{
		changeTrigger = false;
		GetComponent<SpriteAnimator>()->Stop(oldani);	// 再生していたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Play(anipos);	// 新しいアニメーションを再生
	}

	// 弾が撃ちだされている時、処理を終了する
	if (bullet->GetBulletActive() == true)return;
	
	timer++;	// タイマー更新
	// 弾が無い状態で一定時間経つと,shottingへ移行
	if (waittimer <= timer)
	{
		timer = 0;							// リセット
		changeTrigger = true;					// changeSceneを有効にする
		oldani = anipos;					// 再生しているアニメーションを古いものとする
		currentState = GunEnemy::shotting;	// shottingへ移行
	}
	
}

//===============================================================================================
// 発射状態の処理
//===============================================================================================
void GunEnemy::Shotting()
{
	timer++;												// タイマー更新
	
	// 方向を取得
	int dir = GetDirection();
	anipos = (dir * 2) + 1;									// 方向から再生するIDを決定する

	// タイマー更新
	if (changeTrigger == true)
	{
		changeTrigger = false;
		GetComponent<SpriteAnimator>()->Stop(oldani);	// 再生していたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Play(anipos);	// 新しいアニメーションを再生
	}

	
	if (timer >= bulletcreateflame && bullet->GetBulletActive() == false)
	{
		timer = 0;
		std::cout << "弾オブジェクト発射!!\n";
		bullet->SendPos(p_transform->position);			// 発射する直前の自身の位置を送る
		bullet->SetBulletActive(true);					// 弾オブジェクトをアクティブにする
		changeTrigger = true;								// changeSceneを有効にする
		oldani = anipos;								// 再生しているアニメーションを古いものとする
		currentState = GunEnemy::defoult;				// defoultに移行
	}
}

//===============================================================================================
// 死亡状態の処理
//===============================================================================================
void GunEnemy::Dead()
{
	timer++;

	if (changeTrigger == true)
	{
		changeTrigger = false;
		// 当たり判定の停止
		GetComponent<SpriteRenderer>()->SetIsActive(false);

		// 弾オブジェクトの停止
		bullet->SetBulletActive(false);

		// エネミー総数の減少
		CEnemy::DownEnemyCount();
		// 死亡アニメーションを再生する
		/*
		if (direction == 0 || direction == 1)
		{
			anipos = 8;
			GetComponent<SpriteAnimator>()->Play(anipos);
		}
		else
		{
			anipos = 9;
			GetComponent<SpriteAnimator>()->Play(anipos);
		}
		*/
		GetComponent<SpriteAnimator>()->Play(8);
	}

	// アニメーションが終わり次第、オブジェクトの機能を停止する
	if (timer >= deadtime)
	{
		GetComponent<SpriteAnimator>()->Stop(8);
		//GetComponent<SpriteAnimator>()->Stop(anipos);
		GetComponent<GameObjectManager>()->DestroyGameObject(bullet);
		GetComponent<GameObjectManager>()->DestroyGameObject(this);
	}
}

//===============================================================================================
// 当たり判定の処理(OnCollisionEnter)
//===============================================================================================
void GunEnemy::OnCollisionEnter(Collider* _p_col)
{	
	if (life == false)return;
	// 対象のオブジェクトと接触した際、Deadへ移行
	GameObject* col = _p_col->GetGameObject();
	// ヒットした相手が対象のオブジェクトの場合,死亡状態へ
	if (col->GetName() == "Connect" || col->GetName() == "Bomb" || col->GetName() == "Thorn")
	{
		// 処理
		timer = 0;
		changeTrigger = true;
		oldani = anipos;
		currentState = GunEnemy::dead;
		GetComponent<BoxCollider2D>()->SetIsActive(false);		// 当たり判定消去
		bullet->SetBulletActive(false);							// 弾も削除
	}
}