#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"


#include"BiteEnemy.h"
#include"BiteEnemyParam.h"

class BoxCollider2D;

// このエネミーのタグ:"Enemy"

BiteEnemy::BiteEnemy()
{
	
}

BiteEnemy::~BiteEnemy()
{

}

// 初期化=============================================================
void BiteEnemy::Init(const int& direction)
{
	timer = 0;	// タイマーの初期化
	tag = BiteEnemyParam::tag;	// タグ:Enemy
	anipos = BiteEnemyParam::anipos;
	oldani = BiteEnemyParam::oldani;
	hitstoptime = BiteEnemyParam::hitstoptime;	// ヒットストップ時間
	currentState = BiteEnemy::defoult1;		// 通常状態からスタート
	defoulttime_1 = BiteEnemyParam::defoult1;	// 通常状態1でかかるフレーム
	defoulttime_2 = BiteEnemyParam::defoult2;	// 通常状態2でかかるフレーム
	attacktime = BiteEnemyParam::attack;		// 攻撃状態でかかるフレーム
	spinttime = BiteEnemyParam::spin;			// 回転状態でかかるフレーム
	deadtime = BiteEnemyParam::dead;			// 死亡状態でかかるフレーム
	if (direction < 4 && direction >= 0) { SetDirection(direction); }	// 引数が範囲外の数値だった場合,右向きで初期化
	else { SetDirection(0); }
	
	if (direction == 0){ anipos = 0;}
	else if (direction == 1) { anipos = 1;}
	else if (direction == 2) { anipos = 2;}
	else{ anipos = 3;}

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
			for (int i = 0; i < flameraito; i++)
			{
				anim.GetCellRef(i).flame = flameraito;
			}
			p_spriteAnimator->AddAnimation(anim);
		}
	}
	
	// 本体のコライダーの設定
	bodyCollider = AddComponent<BoxCollider2D>();
	
	// 攻撃マスの位置を自身のサイズ分,ずらす
	const hft::HFFLOAT3 size = bodyCollider->GetSize();
	offset[0] = { size.x,0.0f,0.0f };
	offset[1] = { 0.0f,size.y,0.0f };
	offset[2] = { -(size.x),0.0f,0.0f };
	offset[3] = { 0.0f,-(size.y),0.0f };

	//攻撃マスの設定
	attackCollider = AddComponent<BoxCollider2D>();
	attackCollider->SetSize(bodyCollider->GetSize());	// 本体と同じサイズ
	attackCollider->SetOffset({ size.x,0.0f,0.0f });		// 初期は右に出現させる
	attackCollider->SetIsActive(false);

	std::cout << "BiteEnemyパラメータ完了\n";
}

// 更新===============================================================
void BiteEnemy::Update()
{
	timer++;
	
	switch (currentState)
	{
	case defoult1:Defoult1();break;
	//case defoult2:Defoult2();break;
	//case attack:Attack();break;
	//case spin:Spin();break;
	//case dead:Dead();break;
	default:std::cout << "状態エラー\n";
	}
	
}


//==================================================================================
// 通常状態の行動
//==================================================================================
void BiteEnemy::Defoult1()
{
	// 方向を取得
	int dir = GetDirection();
	////デバック用
	std::cout << "通常状態1実行中\n";
	std::cout << "現在の方向:" << GetDirection() << "\n";

	if (changeState == true)
	{
		changeState = false;
		// この状態に変わった際、一回のみ実行される
		if (dir == 2)
		{
			// 方向によるアニメーションの反転あり
		}
		else
		{
			// 方向によるアニメーションの反転なし
		}
		// 再生されていたアニメーションをストップ
		GetComponent<SpriteAnimator>()->Stop(oldani);
	}
	
	if (startState == true)
	{
		startState = false;
		// 方向からアニメーションを決定する
		
	}
	GetComponent<SpriteAnimator>()->Play(12);
	
	if (timer >= defoulttime_1)
	{
		currentState = BiteEnemy::attack;
		timer = 0;
		changeState = true;
		oldani = anipos;	// 現在のアニメーションIDを古いものとする
		anipos++;
	}
	
}

/*
//==================================================================================
// 攻撃状態の行動
//==================================================================================
void BiteEnemy::Attack()
{
	std::cout << "攻撃状態実行中\n";
	int dir = 0;
	if (dir < 0 || dir >= 4)dir = 0;
	attackCollider->SetOffset(offset[dir]);
	attackCollider->SetOffset(offset[GetDirection()]);
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3);
	GetComponent<SpriteAnimator>()->Play((GetDirection() * 3) + 1);
	attackCollider->SetIsActive(true);			// 当たり判定をアクティブに
	if (timer > attacktime)
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
	std::cout << "回転状態実行中\n";
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3);
	GetComponent<SpriteAnimator>()->Play((GetDirection() * 3) + 2);
	if (timer > spinttime)
	{
		GetComponent<SpriteAnimator>()->Stop((GetDirection() * 3) + 2);
		currentState = BiteEnemy::defoult1;		// 通常状態へ
		SetDirection(GetDirection() + 1);		// 方向変換
		if (GetDirection() >= 4) { SetDirection(0); }
		timer = 0;
	}
}


//==================================================================================
// 死亡状態の行動
//==================================================================================
void BiteEnemy::Dead()
{
	CEnemy::DownEnemyCount();
	// 当たり判定停止
	bodyCollider->SetIsActive(false);
	attackCollider->SetIsActive(false);
	// アニメーション
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3);
	GetComponent<SpriteAnimator>()->Stop((GetDirection() * 3) + 1);
	GetComponent<SpriteAnimator>()->Stop((GetDirection() * 3) + 2);
	GetComponent<SpriteAnimator>()->Play(12);
	if (timer > dead)
	{
		std::cout << "BiteEnemy機能停止\n";
		SetIsActive(false);
	}
}*/


//@brief	コライダー同士が衝突した際の処理
// @param	Collider2D* _p_col	2D用コライダーのポインタ
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
			//currentState = BiteEnemy::dead;
		}
	}
	else if (_p_col == attackCollider)
	{
		// 攻撃がヒット
		std::cout << "BiteEnemyの攻撃がヒット\n";
		return;
	}
}