#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include"../../01-TrackObject/04_Enemy/BombEnemy.h"
#include"../../../../00-HEW2026/01-GamaeObject/01-TrackObject/04-Player/PlayerObject.h"
#include"../../01-TrackObject/02_ThornObject/ThormObject.h"
#include"../../01-TrackObject/03_ConnectObject/ConnectObject.h"
#include"../../../../00-HEW2026/01-GamaeObject/01-TrackObject/05-BulletObject/BulletObject.h"
#include"../../../../01-MyLib/06-GameObject/999-GameObjectManager/GameObjectManager.h"
#include"../../../../01-MyLib/08-Scene/02-SceneManager/SceneManager.h"
#include"../../../../01-MyLib/03-Sound/Fsound.h"
#include"BiteEnemy.h"
#include"BiteEnemyParam.h"

class BoxCollider2D;

// このエネミーのタグ:"Bite"


std::vector<AttackMass*> BiteEnemy::ptr_num;

// コンストラクタ
BiteEnemy::BiteEnemy()
{
	name = "Bite";
}

// デストラクタ
BiteEnemy::~BiteEnemy()
{
	if (attackCollider) { delete attackCollider; attackCollider = nullptr; }
}

//==================================================================================
// 本体の初期化処理
//==================================================================================
void BiteEnemy::Init(const int& direction)
{
	for (auto num : ptr_num)delete num;
	ptr_num.clear();

	timer = 0;										// タイマーの初期化
	tag = BiteEnemyParam::tag;						// タグ:Bite
	currentState = BiteEnemy::defoult1;				// 通常状態からスタート
	defoulttime_1 = BiteEnemyParam::defoult1;		// 通常状態1でかかるフレーム
	defoulttime_2 = BiteEnemyParam::defoult2;		// 通常状態2でかかるフレーム
	attacktime = BiteEnemyParam::attack;			// 攻撃状態でかかるフレーム
	spinttime = BiteEnemyParam::spin;				// 回転状態でかかるフレーム
	deadtime = BiteEnemyParam::dead;				// 死亡状態でかかるフレーム
	anipos = BiteEnemyParam::anipos;				// 再生アニメーションの初期化(0)
	oldani = BiteEnemyParam::oldani;				// 停止アニメーションの初期化(0)
	startTrigger = BiteEnemyParam::startTrigger;	// 開始時に一度だけ実行される
	changeTrigger = BiteEnemyParam::changeTrigger;	// シーン切り替え後に一度だけ実行される
	attackCreate = BiteEnemyParam::attackCreate;	// 攻撃判定を出すタイミング
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
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(8,10));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	float flameraito = 0;		// フレームレート
	float flamespead = 0;		// 再生スピード

	// 通常アニメーション
	{
		{ // 右向き
			flameraito = 10;
			flamespead = 10;
			SpriteAnimation anim(div, { 7,6 }, flameraito);
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
			flameraito = 9;
			flamespead = 7;
			SpriteAnimation anim(div, { 5,8 }, flameraito);
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
			flameraito = 9;
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
			SpriteAnimation anim(div, { 0,6 }, flameraito);
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
			SpriteAnimation anim(div, { 5,3 }, flameraito);
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
			SpriteAnimation anim(div, { 2,5 }, flameraito);
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
			SpriteAnimation anim(div, { 7,2 }, flameraito);
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
		{
			// 左向き
			flameraito = 4;
			flamespead = 4;
			SpriteAnimation anim1(div, { 6,3 }, flameraito);
			anim1.InActive();
			anim1.SetID(12);
			anim1.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim1.SetPriority(0);
			flamespead = 15;
			for (int i = 0; i < flameraito; i++)
			{
				anim1.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim1);
		}

		{
			// 右向き
			flameraito = 4;
			flamespead = 4;
			SpriteAnimation anim1(div, { 1,8 }, flameraito);
			anim1.InActive();
			anim1.SetID(13);
			anim1.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim1.SetPriority(0);
			flamespead = 15;
			for (int i = 0; i < flameraito; i++)
			{
				anim1.GetCellRef(i).flame = flamespead;
			}
			p_spriteAnimator->AddAnimation(anim1);
		}

	}
	
	// 本体のコライダーの設定
	auto bodyCollider = AddComponent<BoxCollider2D>();
	bodyCollider->SetSize(p_transform->scale);					// 本体のサイズ分当たり判定をとる
	bodyCollider->SetIsActive(true);

	//攻撃マスの初期化
	attackCollider = new AttackMass;
	attackCollider->Init();
	attackCollider->SetFg(false);
	attackCollider->SendDir(direction);

	//SE_Bite = SoundManager::AddSound("Assets/03-Sound/02-Enemy/Bite_attack.wav");
	//SE_Dead = SoundManager::AddSound("Assets/03-Sound/02-Enemy/Enemy_Dead.wav");
}

//==================================================================================
// 本体の更新処理
//==================================================================================
void BiteEnemy::Update()
{
	attackCollider->SendPos(p_transform->position);		// 座標を攻撃マスに送る
	attackCollider->UpdatePos();						// 座標を更新

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

	// シーン遷移
	if (SceneManager::GetInstance().GetNext())
	{
		if (attackCollider)
		{
			attackCollider->GetComponent<BoxCollider2D>()->SetIsActive(false);
			attackCollider->GetComponent<SpriteRenderer>()->SetIsActive(false);
			ptr_num.push_back(attackCollider);
			attackCollider = nullptr;
		}

		GetComponent<BoxCollider2D>()->SetIsTrigger(false);
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

	// 通常状態の残りフレームが4分の3を切ると、攻撃判定を可視化する
	if (timer > defoulttime_1 / 4)
	{
		attackCollider->GetComponent<SpriteRenderer>()->SetIsActive(true);
		attackCollider->MassFrash();
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
	attackCollider->MassFrash();						// マスを光らす

	// 方向を取得
	int dir = GetDirection();

	if (changeTrigger == true)
	{
		changeTrigger = false;	
		GetComponent<SpriteAnimator>()->Stop(oldani);		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);
	}

	if (timer == attackCreate)
	{
		// 攻撃前にも送る
		//SoundManager::GetInstance().Play(SE_Bite);
		attackCollider->UpdatePos();							// 座標を更新
		attackCollider->MassFrash();							// マスを表示
		attackCollider->SendDir(dir);							// 方向を送る
		attackCollider->SetFg(true);							// 攻撃をアクティブ
	}
	//std::cout << "攻撃判定のX座標:" << attackCollider.attackCollider->GetOffset().x << "Y座標:" << attackCollider.attackCollider->GetOffset().y << "Z座標:" << attackCollider.attackCollider->GetOffset().z << "\n";
	if (timer > attacktime)
	{
		changeTrigger = true;
		currentState = BiteEnemy::defoult2;					// 通常状態へ
		attackCollider->SetFg(false);						// 攻撃を非アクティブ
		timer = 0;
		anipos++;
		oldani = Act[anipos] + dir;
		attackCollider->GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 0, 0, 0, 0.0 };
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
		oldani = Act[anipos] + dir;								// 現在のアニメーションIDを古いものとする
		anipos++;
		attackCollider->SendDir(direction);						// 方向を送る
	}
}

//==================================================================================
// 死亡状態の処理
//==================================================================================
void BiteEnemy::Dead()
{
	CEnemy::DownEnemyCount();			// エネミー総数の減少
	// 方向を取得
	int dir = GetDirection();

	if (changeTrigger == true)
	{
		//SoundManager::GetInstance().Play(SE_Dead);
		GameObjectManager::GetInstance().Stop(300);
		Sleep(100);
		changeTrigger = false;
		// 再生されていたアニメーションをストップ
		if (dir == 0 || dir == 1)
		{
			anipos = 13;
			GetComponent<SpriteAnimator>()->Stop(oldani);
			GetComponent<SpriteAnimator>()->Play(anipos);
		}
		else
		{
			anipos = 12;
			GetComponent<SpriteAnimator>()->Stop(oldani);
			GetComponent<SpriteAnimator>()->Play(anipos);
		}
	}
	
	if (timer >= deadtime)
	{
		timer = 0;
		GetComponent<SpriteAnimator>()->Stop(anipos);
		GetComponent<SpriteRenderer>()->SetIsActive(false);					// 描写停止
		GameObjectManager::GetInstance().RemoveGameObject(attackCollider);	// 攻撃マスの活動停止
		GameObjectManager::GetInstance().RemoveGameObject(this);			// 活動停止
	}
}

//===================================================================================
// 本体にヒットした際の処理(OnCollisionEnter)
//===================================================================================
void BiteEnemy::OnCollisionEnter(Collider* _p_col)
{
	// 接触相手の情報を取得
	GameObject* col = _p_col->GetGameObject();
	// ヒットした相手が対象のオブジェクトの場合,死亡状態へ
	if (col->GetName() == "Bomb" || col->GetName() == "Connect" || col->GetName() == "Thron")
	{
		// 処理
		timer = 0;																// タイマー初期化
		oldani = anipos;														// 現在のアニメーションを古いアニメーションとする
		currentState = BiteEnemy::dead;											// 死亡状態へ移行
		changeTrigger = true;													// 死亡状態の一度だけ処理されるのをアクティブに
		attackCollider->GetComponent<SpriteRenderer>()->SetIsActive(false);		// 可視化されているマスの表示をOFF
		attackCollider->SetFg(false);											// 攻撃判定を消す
		GetComponent<BoxCollider2D>()->SetIsTrigger(false);						// 自身の当たり判定を消す
		GetComponent<BoxCollider2D>()->SetIsActive(false);						// 自身の当たり判定を消す
	
	}
}

//*
//*  本体とOnCollisionEnterの処理と攻撃判定のOnCollisionEnterの処理が被ってしまうため、攻撃判定をクラスにして本体に持たせてます
//*

AttackMass::~AttackMass()
{
	GetComponent<BoxCollider2D>()->SetIsActive(false);
	GetComponent<SpriteRenderer>()->SetIsActive(false);
}

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
	auto attackCollider = AddComponent<BoxCollider2D>();
	hft::HFFLOAT3 p_size = p_transform->scale;		
	attackCollider->SetSize(p_size);				// 当たり判定の大きさはサイズと同じ
	attackCollider->SetIsActive(false);				// 判定を出さない
	GetComponent<SpriteRenderer>()->SetIsActive(false);
}

//===================================================================================
// 攻撃判定の更新
//===================================================================================
void AttackMass::Update()
{
	// フラグがtrueであればアクティブ
	if (GetFg() == true)
	{
		UpdatePos();		// 方向による判定の座標更新
		GetComponent<BoxCollider2D>()->SetIsActive(true);
		GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1, 0, 0, 0.5 };
	}
	else
	{
		GetComponent<BoxCollider2D>()->SetIsActive(false);
	}

	// デバック用
	//std::cout << "X座標:" << p_transform->position.x << "Y座標:" << p_transform->position.y << "Z座標:" << p_transform->position.z << "\n";
}

//===================================================================================
// 方向によって、攻撃判定の位置を変える関数
//===================================================================================
void AttackMass::UpdatePos()
{
	// 中心となる座標を更新
	p_transform->position = acceptPos;
	switch (direction) {
	case 0:p_transform->position.x = acceptPos.x + 120; break;
	case 1:p_transform->position.y = acceptPos.y + 120; break;
	case 2:p_transform->position.x = acceptPos.x - 120; break;
	case 3:p_transform->position.y = acceptPos.y - 120; break;
	}

	// デバック用
	//hft::HFFLOAT3 ShowOff = p_transform->position;
	//std::cout << "===========================================================================\n";
	//std::cout << "X座標:" << ShowOff.x << "Y座標:" << ShowOff.y << "Z座標:" << ShowOff.z << "\n";
}

//===================================================================================
// 攻撃判定が出るマスを可視化する関数
//===================================================================================
void AttackMass::MassFrash()
{
	if (Fg == true){GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1, 0, 0, 0.5 };}
	else { GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1, 1, 0, 0.5 };}
}

//===================================================================================
// 攻撃判定にヒットした際の処理(OnCollisionEnter)
//===================================================================================
void AttackMass::OnCollisionEnter(Collider* _p_col)
{
	// 接触相手の情報を取得
	GameObject* col = _p_col->GetGameObject();
	if (col->GetName() != "Player")return;
	GetComponent<BoxCollider2D>()->SetIsActive(false);
}