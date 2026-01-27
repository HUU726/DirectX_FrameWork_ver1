#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"


#include"BiteEnemy.h"
#include"BiteEnemyParam.h"

class BoxCollider2D;

// このエネミーのタグ:"Bite"

BiteEnemy::BiteEnemy()
{
	
}

BiteEnemy::~BiteEnemy()
{

}

// 初期化=============================================================
void BiteEnemy::Init(const int& direction)
{
	timer = 0;									// タイマーの初期化
	tag = BiteEnemyParam::tag;					// タグ:Bite
	anipos = BiteEnemyParam::anipos;
	oldani = BiteEnemyParam::oldani;
	hitstoptime = BiteEnemyParam::hitstoptime;	// ヒットストップ時間
	currentState = BiteEnemy::defoult1;			// 通常状態からスタート
	defoulttime_1 = BiteEnemyParam::defoult1;	// 通常状態1でかかるフレーム
	defoulttime_2 = BiteEnemyParam::defoult2;	// 通常状態2でかかるフレーム
	attacktime = BiteEnemyParam::attack;		// 攻撃状態でかかるフレーム
	spinttime = BiteEnemyParam::spin;			// 回転状態でかかるフレーム
	deadtime = BiteEnemyParam::dead;			// 死亡状態でかかるフレーム

	// 引数が範囲外の数値だった場合,右向きで初期化
	if (direction < 4 && direction >= 0) { SetDirection(direction); }	
	else { SetDirection(0); }
	
	// 行動シーケンス(// 通常→攻撃→通常→回転→...)
	for (int i = 0; i < 4; i++)
	{
		Act[i] = BiteEnemyParam::Act[i];
	}

	// 位置の設定
	{
		p_transform->scale = BiteEnemyParam::scale;
		p_transform->position = BiteEnemyParam::position;
	}

	// レンダラーの設定
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(BiteEnemyParam::BiteEnemyTexName);
	// アニメーターの設定
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(8.0f, 8.0f));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	float flameraito = 0;
	float flamespead = 0;
	// 引数: 分割数, 開始位置(x,y), コマ数
	// 通常アニメーション
	{
		{
			flameraito = 10;
			SpriteAnimation anim(div, { 0,0 }, flameraito);
			anim.InActive();
			anim.SetID(0);
			anim.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		
		{
			flameraito = 10;
			SpriteAnimation anim(div, { 4,2 }, flameraito);
			anim.InActive();
			anim.SetID(1);
			anim.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}
		
		{

			flameraito = 10;
			SpriteAnimation anim(div, { 0,0 }, flameraito);
			anim.InActive();
			anim.SetID(2);
			anim.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);

		}

		{
			flameraito = 10;
			SpriteAnimation anim(div, { 2,1 }, flameraito);
			anim.InActive();
			anim.SetID(3);
			anim.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}
	}

	// 攻撃アニメーション
	{
		{
			flameraito = 7;
			SpriteAnimation anim(div, { 2,4 }, flameraito);
			anim.InActive();
			anim.SetID(4);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}


		{
			flameraito = 6;
			SpriteAnimation anim(div, { 1,6 }, flameraito);
			anim.InActive();
			anim.SetID(5);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		{
			flameraito = 7;
			SpriteAnimation anim(div, { 2,4 }, flameraito);
			anim.InActive();
			anim.SetID(6);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		{
			flameraito = 6;
			SpriteAnimation anim(div, { 3,5 }, flameraito);
			anim.InActive();
			anim.SetID(7);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}
	}
	
	// 回転
	{
		{
			flameraito = 2;
			SpriteAnimation anim(div, { 1,1 }, flameraito);
			anim.InActive();
			anim.SetID(8);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		{
			flameraito = 2;
			SpriteAnimation anim(div, { 1,1 }, flameraito);
			anim.InActive();
			anim.SetID(9);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		{
			flameraito = 2;
			SpriteAnimation anim(div, { 5,3 }, flameraito);
			anim.InActive();
			anim.SetID(10);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}

		{
			flameraito = 2;
			SpriteAnimation anim(div, { 5,3 }, flameraito);
			anim.InActive();
			anim.SetID(11);
			anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
			anim.SetPriority(0);
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}
	}

	// 死亡
	{
		{
			flameraito = 4;
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
	}
	
	// 本体のコライダーの設定
	bodyCollider = AddComponent<BoxCollider2D>();
	hft::HFFLOAT3 p_size = { 100.f,100.f,0.f };
	bodyCollider->SetSize(p_size);					// 本体のサイズ分当たり判定をとる
	// 攻撃マスの判定を自身のサイズ分,ずらす
	/*
	const hft::HFFLOAT3 size = bodyCollider->GetSize();
	offset[0] = { size.x,0.0f,0.0f };
	offset[1] = { 0.0f,size.y,0.0f };
	offset[2] = { (size.x * -1),0.0f,0.0f };
	offset[3] = { 0.0f,(size.y * -1),0.0f };
	*/

	//攻撃マスの設定
	attackCollider.Init();

	/*
	attackCollider.attackCollider = AddComponent<BoxCollider2D>();
	attackCollider.attackCollider->SetSize(bodyCollider->GetSize());	// 本体と同じサイズ
	attackCollider.attackCollider->SetOffset(offset[GetDirection()]);
	attackCollider.attackCollider->SetIsActive(true);
	attackCollider.attackCollider->SetIsTrigger(false);

	// ===== デバッグ用：攻撃判定の可視化 =====
	attackCollider.attackform = attackCollider.AddComponent<SpriteRenderer>();
	attackCollider.attackform->LoadTexture("Assets/01-Texture/02-Player/Ritu_animations.png");   // プレイヤーの画像
	attackCollider.attackform->SetIsActive(false);
	*/
}

// 更新===============================================================
void BiteEnemy::Update()
{
	timer++;
	
	switch (currentState)
	{
	case State::defoult1:Defoult1();break;
	case State::defoult2:Defoult2();break;
	case State::attack:Attack();break;
	case State::spin:Spin();break;
	case State::dead:Dead();break;
	default:std::cout << "状態エラー\n";
	}
	//attackCollider.Update(p_transform->position, GetDirection());
}


//==================================================================================
// 通常状態1の処理
//==================================================================================
void BiteEnemy::Defoult1()
{
	// 方向を取得
	int dir = GetDirection();
	if (changeState == true)
	{
		changeState = false;
		if (anipos >= 4) { anipos = 0; }
		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Stop(oldani);
		GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);
	}
	// 最初に再生するアニメーション(この書き方をするのは古いアニメーションが無いため)
	if (startState == true)
	{
		startState = false;
		// 方向からアニメーションを決定する
		GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);
	}
	// 時間を超えた場合
	if (timer >= defoulttime_1)
	{
		currentState = BiteEnemy::attack;
		timer = 0;
		changeState = true;
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

	if (changeState == true)
	{
		changeState = false;	
		//attackCollider.SetOffset(offset[dir]);			// 攻撃マスの位置を調整
		GetComponent<SpriteAnimator>()->Stop(oldani);		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);
		attackCollider.SetFg(true);							// デバック用
		//attackCollider.SetIsTrigger(true);				// デバック用(当たり判定)
		//attackCollider.SetIsActive(true);					// デバック用(描写用)
	}
	//std::cout << "攻撃判定のX座標:" << attackCollider.attackCollider->GetOffset().x << "Y座標:" << attackCollider.attackCollider->GetOffset().y << "Z座標:" << attackCollider.attackCollider->GetOffset().z << "\n";
	if (timer > attacktime)
	{
		currentState = BiteEnemy::defoult2;					// 通常状態へ
		attackCollider.SetFg(false);							// デバック用
		//attackCollider.SetIsTrigger(false);					// デバック用(当たり判定)
		//attackCollider.SetIsActive(false);					// デバック用(描写用)
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
	if (changeState == true)
	{
		changeState = false;
		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Stop(oldani);
	}
	GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);

	if (timer >= defoulttime_2)
	{
		currentState = BiteEnemy::spin;
		timer = 0;
		changeState = true;
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

	if (changeState == true)
	{
		changeState = false;
		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Stop(oldani);

	}

	GetComponent<SpriteAnimator>()->Play(Act[anipos] + dir);

	if (timer >= spinttime)
	{
		currentState = BiteEnemy::defoult1;
		timer = 0;
		changeState = true;
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
	
	// 方向を取得
	int dir = GetDirection();

	if (changeState == true)
	{
		changeState = false;
		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Stop(oldani);
		GetComponent<SpriteAnimator>()->Play(12);
	}
	
	if (timer >= deadtime)
	{
		timer = 0;
		this->SetIsActive(false);
		this->SetIsRender(false);
	}
}

//@brief	コライダー同士が衝突した際の処理
// @param	Collider2D* _p_col	2D用コライダーのポインタ
void BiteEnemy::OnCollisionEnter(Collider* _p_col)// ヒットした相手のコライダー
{
	// 接触相手の情報を取得
	GameObject* col = _p_col->GetGameObject();

	if (bodyCollider == _p_col)
	{

	}

	// 対象オブジェクトの場合、deadへ移行
	
	
	if (col->GetTag() == "Bullet" || col->GetTag() == "DamageObject" || col->GetTag() == "Thorn" || col->GetTag() == "Connect")
	{
		timer = 0;
		std::cout << col->GetTag()<<"\n";
		//std::cout << "BIteEnemy本体にヒット\n";
		oldani = anipos;
		currentState = BiteEnemy::dead;
		changeState = true;
		attackCollider.SetFg(false);		// 攻撃判定を消す
	}
	
}

void AttackMass::Init()
{
	attackRenderer = new GameObject2D;
	// パラメータ初期化
	tag = "Enemy";
	p_transform->position = { 0.0f,0.0f,0.0f };
	p_transform->scale = { 70.f,70.f,1.f };
	// 当たり判定の追加
	attackCollider = AddComponent<BoxCollider2D>();
	hft::HFFLOAT3 p_size = p_transform->scale;		// 当たり判定の大きさは本体のサイズと同じ
	attackCollider->SetSize(p_size);
	// レンダラーの設定
	//std::shared_ptr<Texture> tex1 = attackRenderer->GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/wave.png");
	//SetFg(false);
	SpriteRenderer* renderer = attackRenderer->GetComponent<SpriteRenderer>();
	renderer->LoadTexture("Assets/01-Texture/99-Test/wave.png");
	GetComponent<SpriteRenderer>()->SetIsActive(false);
}

//	
void AttackMass::Update(hft::HFFLOAT3 NewPos,const int& direction)
{
	p_transform->position = NewPos;
	switch (direction) {
	case 0:p_transform->position.x += 75; break;
	case 1:p_transform->position.y += 75; break;
	case 2:p_transform->position.x -= 75; break;
	case 3:p_transform->position.y -= 75; break;
	}

	if (Fg == true)
	{
		//std::cout << attackCollider->GetIsTrigger()<<"\n";
		//std::cout << attackRenderer->GetIsActive() << "\n";
		GetComponent<BoxCollider2D>()->SetIsTrigger(true);
		attackRenderer->SetIsActive(true);
	}
	else
	{
		//std::cout << attackCollider->GetIsTrigger() << "\n";
		//std::cout << attackRenderer->GetIsActive() << "\n";
		attackCollider->SetIsTrigger(false);
		attackRenderer->SetIsActive(false);
	}

	// デバック用
	//std::cout << "X座標:" << p_transform->position.x << "Y座標:" << p_transform->position.y << "Z座標:" << p_transform->position.z << "\n";
}

// 攻撃マスのOnCillisionEnter
void AttackMass::OnCollisionEnter(Collider* _p_col)
{
	// 接触相手の情報を取得
	GameObject* col = _p_col->GetGameObject();
	if (col->GetTag() == "Bom")
	{
		std::cout << "攻撃判定にヒット\n";
	}
}