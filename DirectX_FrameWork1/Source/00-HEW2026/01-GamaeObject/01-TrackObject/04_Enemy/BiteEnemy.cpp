#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include"../../01-TrackObject/04_Enemy/BombEnemy.h"
#include"../../01-TrackObject/02_ThornObject/ThormObject.h"
#include"../../01-TrackObject/03_ConnectObject/ConnectObject.h"

#include"BiteEnemy.h"
#include"BiteEnemyParam.h"

class BoxCollider2D;

// このエネミーのタグ:"Bite"

// コンストラクタ
BiteEnemy::BiteEnemy()
{
	bodyCollider = nullptr;
}

//==================================================================================
// 本体の初期化処理
//==================================================================================
void BiteEnemy::Init(const int& direction)
{
	timer = 0;									// タイマーの初期化
	
	tag = BiteEnemyParam::tag;					// タグ:Bite
	currentState = BiteEnemy::defoult1;			// 通常状態からスタート
	defoulttime_1 = BiteEnemyParam::defoult1;	// 通常状態1でかかるフレーム
	defoulttime_2 = BiteEnemyParam::defoult2;	// 通常状態2でかかるフレーム
	attacktime = BiteEnemyParam::attack;		// 攻撃状態でかかるフレーム
	spinttime = BiteEnemyParam::spin;			// 回転状態でかかるフレーム
	deadtime = BiteEnemyParam::dead;			// 死亡状態でかかるフレーム
	anipos = BiteEnemyParam::anipos;			// 再生アニメーションの初期化(0)
	oldani = BiteEnemyParam::oldani;			// 停止アニメーションの初期化(0)
	startTrigger = BiteEnemyParam::startTrigger;	// 開始時に一度だけ実行される
	changeTrigger = BiteEnemyParam::changeTrigger;	// シーン切り替え後に一度だけ実行される

	// 引数が範囲外の数値だった場合,右向きで初期化
	if (direction < 4 && direction >= 0) { SetDirection(direction); }	
	else { SetDirection(0); }
	
	// 行動シーケンス(// 通常→攻撃→通常→回転→...繰り返し)
	for (int i = 0; i < 4; i++)
	{
		Act[i] = BiteEnemyParam::Act[i];
	}

	// 位置の設定
	{
		p_transform->scale = BiteEnemyParam::scale;			// 大きさの初期化
		p_transform->position = BiteEnemyParam::position;	// 座標の初期化
	}

	// レンダラーの設定
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(BiteEnemyParam::BiteEnemyTexName);
	// アニメーターの設定
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(8, 8));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	float flameraito = 0;		// フレームレート
	float flamespead = 0;		// 再生スピード

	// 通常アニメーション
	{
		{ // 右向き
			flameraito = 10;
			flamespead = 10;
			SpriteAnimation anim(div, { 0,0 }, flameraito);
			anim.InActive();
			anim.SetID(0);
			anim.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		
		{ // 上向き
			flameraito = 10;
			flamespead = 10;
			SpriteAnimation anim(div, { 4,2 }, flameraito);
			anim.InActive();
			anim.SetID(1);
			anim.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}
		
		{ // 左向き
			flameraito = 10;
			flamespead = 10;
			SpriteAnimation anim(div, { 0,0 }, flameraito);
			anim.InActive();
			anim.SetID(2);
			anim.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);

		}

		{ // 下向き
			flameraito = 10;
			flamespead = 10;
			SpriteAnimation anim(div, { 2,1 }, flameraito);
			anim.InActive();
			anim.SetID(3);
			anim.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}
	}

	// 攻撃アニメーション
	{
		{ // 右向き
			flameraito = 7;
			flamespead = 7;
			SpriteAnimation anim(div, { 2,4 }, flameraito);
			anim.InActive();
			anim.SetID(4);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}


		{ // 上向き
			flameraito = 6;
			flamespead = 6;
			SpriteAnimation anim(div, { 1,6 }, flameraito);
			anim.InActive();
			anim.SetID(5);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		{ // 左向き
			flameraito = 7;
			flamespead = 7;
			SpriteAnimation anim(div, { 2,4 }, flameraito);
			anim.InActive();
			anim.SetID(6);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		{ // 下向き
			flameraito = 6;
			flamespead = 6;
			SpriteAnimation anim(div, { 3,5 }, flameraito);
			anim.InActive();
			anim.SetID(7);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}
	}
	
	// 回転アニメーション
	{
		{ // 右向き
			flameraito = 2;
			flamespead = 2;
			SpriteAnimation anim(div, { 1,1 }, flameraito);
			anim.InActive();
			anim.SetID(8);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		{ // 上向き
			flameraito = 2;
			flamespead = 2;
			SpriteAnimation anim(div, { 1,1 }, flameraito);
			anim.InActive();
			anim.SetID(9);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		{ // 左向き
			flameraito = 2;
			flamespead = 2;
			SpriteAnimation anim(div, { 5,3 }, flameraito);
			anim.InActive();
			anim.SetID(10);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		{ // 下向き
			flameraito = 2;
			flamespead = 2;
			SpriteAnimation anim(div, { 5,3 }, flameraito);
			anim.InActive();
			anim.SetID(11);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim);
		}
	}

	// 死亡アニメーション
	{
		// 一方向のみ
		flameraito = 4;
		flamespead = 4;
		SpriteAnimation anim(div, { 6,3 }, flameraito);
		anim.InActive();
		anim.SetID(12);
		anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim.SetPriority(0);
		flamespead = 15;
		for (int i = 0; i < flameraito; i++)
		{
			anim.GetCellRef(i).flame = flamespead;
		}
		p_spriteAnimator->AddAnimation(anim);
	}
	
	// 本体のコライダーの設定
	bodyCollider = AddComponent<BoxCollider2D>();
	hft::HFFLOAT3 p_size = { 100.f,100.f,0.f };
	bodyCollider->SetSize(p_size);					// 本体のサイズ分当たり判定をとる

	//攻撃マスの初期化
	attackCollider.Init();
}


//==================================================================================
// 本体の更新処理
//==================================================================================
void BiteEnemy::Update()
{
	timer++;	// タイマー更新
	
	switch (currentState)
	{
	case State::defoult1:Defoult1();break;
	case State::defoult2:Defoult2();break;
	case State::attack:Attack();break;
	case State::spin:Spin();break;
	case State::dead:Dead();break;
	default:std::cout << "状態エラー\n";
	}
}


//==================================================================================
// 通常状態1の処理
//==================================================================================
void BiteEnemy::Defoult1()
{
	// 方向を取得
	int dir = GetDirection();
	if (changeTrigger == true)
	{
		changeTrigger = false;
		if (anipos >= 4) { anipos = 0; }
		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Stop(oldani);
		GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);
	}
	// 最初に再生するアニメーション(この書き方をするのは古いアニメーションが無いため)
	if (startTrigger == true)
	{
		startTrigger = false;
		// 方向からアニメーションを決定する
		GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);
	}
	// 時間を超えた場合
	if (timer >= defoulttime_1)
	{
		currentState = BiteEnemy::attack;
		timer = 0;
		changeTrigger = true;
		oldani = Act[anipos] + dir;	// 現在のアニメーションIDを古いものとする
		anipos++;
	}	
}

//==================================================================================
// 攻撃状態の処理
//==================================================================================
void BiteEnemy::Attack()
{
	// 方向を取得
	int dir = GetDirection();

	//================================================================
	// (変更予定)座標は常に送り続ける
	//================================================================
	attackCollider.SendPos(p_transform->position);		

	if (changeTrigger == true)
	{
		changeTrigger = false;	
		GetComponent<SpriteAnimator>()->Stop(oldani);		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);
		//================================================================
		// (変更予定)攻撃判定に現在の方向を送ってからアクティブにする
		//================================================================
		attackCollider.SendDir(direction);
		attackCollider.UpdateOffset();
		attackCollider.SetFg(true);							// デバック用
	}
	//std::cout << "攻撃判定のX座標:" << attackCollider.attackCollider->GetOffset().x << "Y座標:" << attackCollider.attackCollider->GetOffset().y << "Z座標:" << attackCollider.attackCollider->GetOffset().z << "\n";
	if (timer > attacktime)
	{
		changeTrigger = true;
		currentState = BiteEnemy::defoult2;					// 通常状態へ
		attackCollider.SetFg(false);						// デバック用
		timer = 0;
		anipos++;
		oldani = Act[anipos] + dir;
	}
}

//==================================================================================
// 通常状態2の処理
//==================================================================================
void BiteEnemy::Defoult2()
{
	// 方向を取得
	int dir = GetDirection();
	if (changeTrigger == true)
	{
		changeTrigger = false;
		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Stop(oldani);
	}
	GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);

	if (timer >= defoulttime_2)
	{
		currentState = BiteEnemy::spin;
		timer = 0;
		changeTrigger = true;
		oldani = Act[anipos] + dir;	// 現在のアニメーションIDを古いものとする
		anipos++;
	}
}

//==================================================================================
// 回転状態の処理
//==================================================================================
void BiteEnemy::Spin()
{
	// 方向を取得
	int dir = GetDirection();

	if (changeTrigger == true)
	{
		changeTrigger = false;
		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Stop(oldani);

	}

	GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);

	if (timer >= spinttime)
	{
		currentState = BiteEnemy::defoult1;
		timer = 0;
		changeTrigger = true;
		SetDirection(dir + 1);
		if (dir == 3) { SetDirection(0); }
		oldani = Act[anipos] + dir;	// 現在のアニメーションIDを古いものとする
		anipos++;
	}
}

//==================================================================================
// 死亡状態の処理
//==================================================================================
void BiteEnemy::Dead()
{
	CEnemy::DownEnemyCount();			// エネミー総数の減少

	if (changeTrigger == true)
	{
		changeTrigger = false;
		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Stop(oldani);
		GetComponent<SpriteAnimator>()->Play(12);
	}
	
	if (timer >= deadtime)
	{
		timer = 0;
		GetComponent<SpriteAnimator>()->Stop(12);
		GetComponent<BoxCollider2D>()->SetIsTrigger(false);
		this->SetIsRender(false);		// 描写停止
		this->SetIsActive(false);		// 活動停止
	}
}

//===================================================================================
// 本体にヒットした際の処理(OnCollisionEnter)
//===================================================================================
void BiteEnemy::OnCollisionEnter(Collider* _p_col)
{
	// 接触相手の情報を取得
	GameObject* col = _p_col->GetGameObject();
	std::string other_tag = col->GetTag();		// タグ
	
	// ヒットした相手が対象のオブジェクトの場合,死亡状態へ
	// 爆弾の処理
	{
		// 嚙みつく敵の攻撃判定と同じタグを使用しているため,キャストで型を確認する
		TrackObject* ptr = dynamic_cast<BombEnemy*>(col);
		// 爆弾の型ではない場合, ptr に nullptr が格納される
		if (ptr != nullptr)
		{
			if (tag == "Enemy")
			{
				// デバック用
				// std::cout << "BIteEnemy本体に爆弾がヒット\n";

				// 処理
				timer = 0;							// タイマー初期化
				oldani = anipos;					// 現在のアニメーションを古いアニメーションとする
				currentState = BiteEnemy::dead;		// 死亡状態へ移行
				changeTrigger = true;					// 死亡状態の一度だけ処理されるのをアクティブに
				attackCollider.SetFg(false);		// 攻撃判定を消す
			}
		}
	}
	
	// 連結ブロックの処理
	{
		// キャストで相手の型を確認する
		TrackObject* ptr = dynamic_cast<ConnectObject*>(col);
		// 連結する敵の型ではない場合, ptr に nullptr が格納される
		if (ptr != nullptr)
		{
			if (tag == "Enemy")
			{
				// デバック用
				// std::cout << "BIteEnemy本体に連結ブロックがヒット\n";

				// 処理
				timer = 0;							// タイマー初期化
				oldani = anipos;					// 現在のアニメーションを古いアニメーションとする
				currentState = BiteEnemy::dead;		// 死亡状態へ移行
				changeTrigger = true;					// 死亡状態の一度だけ処理されるのをアクティブに
				attackCollider.SetFg(false);		// 攻撃判定を消す
			}
		}
	}

	// 落下トゲの処理
	{
		// キャストで相手の型を確認する
		TrackObject* ptr = dynamic_cast<ThormObject*>(col);
		// 連結する敵の型ではない場合, ptr に nullptr が格納される
		if (ptr != nullptr)
		{
			// デバック用
		// std::cout << "BIteEnemy本体に落下トゲがヒット\n";

		// 処理
			timer = 0;							// タイマー初期化
			oldani = anipos;					// 現在のアニメーションを古いアニメーションとする
			currentState = BiteEnemy::dead;		// 死亡状態へ移行
			changeTrigger = true;					// 死亡状態の一度だけ処理されるのをアクティブに
			attackCollider.SetFg(false);		// 攻撃判定を消す
		}
	}

	/// タグ不要なら、また変えるかも.....
}

//*
//*  本体とOnCollisionEnterの処理と攻撃判定のOnCollisionEnterの処理が被ってしまうため、攻撃判定をクラスにして本体に持たせてます
//*

// このオブジェクトのタグ:"Enemy"
// 
//===================================================================================
// 攻撃判定の初期化
//===================================================================================
void AttackMass::Init()
{
	// パラメータ初期化
	tag = AttackMassParam::tag;							// タグの初期化
	SetFg(AttackMassParam::Fg);							// フラグの初期化
	direction = AttackMassParam::direction;				// 方向の初期化
	p_transform->position = AttackMassParam::position;	// 座標の初期化
	p_transform->scale = AttackMassParam::scale;		// サイズの初期化

	// 当たり判定の追加
	attackCollider = AddComponent<BoxCollider2D>();
	hft::HFFLOAT3 p_size = p_transform->scale;		// 当たり判定の大きさはサイズと同じ
	attackCollider->SetSize(p_size);
	this->SetIsRender(false);						// 攻撃判定を描写しない

	/* デバック用
	// レンダラーの設定
	attackRenderer = new GameObject2D;
	SpriteRenderer* renderer = attackRenderer->GetComponent<SpriteRenderer>();
	renderer->LoadTexture("Assets/01-Texture/99-Test/wave.png");
	GetComponent<SpriteRenderer>()->SetIsActive(false);
	*/
}

//===================================================================================
// 攻撃判定の更新
//===================================================================================
void AttackMass::Update()
{
	// フラグがtrueであればアクティブ
	if (GetFg() == true)
	{
		UpdateOffset();
		GetComponent<BoxCollider2D>()->SetIsTrigger(true);
		// デバック用
		//GetComponent<SpriteRenderer>()->SetIsActive(true);
	}
	else
	{
		GetComponent<BoxCollider2D>()->SetIsTrigger(false);
		// デバック用
		//GetComponent<SpriteRenderer>()->SetIsActive(false);
	}

	// デバック用
	//std::cout << "X座標:" << p_transform->position.x << "Y座標:" << p_transform->position.y << "Z座標:" << p_transform->position.z << "\n";
}

//===================================================================================
// 方向によって、攻撃判定の位置を変える関数
//===================================================================================
void AttackMass::UpdateOffset()
{
	hft::HFFLOAT3 Offset[4] = { {50.f,0.f,0.f},{0.f,50.f,0.f},{-50.f,0.f,0.f}, {0.f,-50.f,0.f} };
	GetComponent<BoxCollider2D>()->SetOffset(Offset[direction]);
	// デバック用
	//hft::HFFLOAT3 ShowOff = GetComponent<BoxCollider2D>()->GetOffset();
	//std::cout << "===========================================================================\n";
	//std::cout << "X座標:" << ShowOff.x << "Y座標:" << ShowOff.y << "Z座標:" << ShowOff.z << "\n";
}

//===================================================================================
// 攻撃判定にヒットした際の処理(OnCollisionEnter)
//===================================================================================
void AttackMass::OnCollisionEnter(Collider* _p_col)
{
	//*ほぼデバック用
	
	// 接触相手の情報を取得
	//GameObject* col = _p_col->GetGameObject();
	/*
	std::cout << "----------------攻撃判定にヒット-----------\n"
	std::cout << "      ヒットしたタグ:"<< col->GetTag() <<"\n";
	*/
}