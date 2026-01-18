#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#include"BiteEnemy.h"

BiteEnemy::BiteEnemy()
{
	
}

BiteEnemy::~BiteEnemy()
{

}

// 初期化=============================================================
void BiteEnemy::Init()
{
	InitParam();	// エネミーのパラメータの初期化
}

// 更新===============================================================
void BiteEnemy::Update()
{
	Bite_Update();				// フレーム、行動の更新
	Bite_Animation();	// アニメーションの更新
}

// パラメータ初期化============================================================
void BiteEnemy::InitParam()
{
	// タイマーの初期化
	timer = 0;

	// パラメータ(別のファイルに移動予定)
	hitstopspead = 1.0f;	// ヒットストップスピード(現在は等速)
	hitstoptime = 10.0f;	// ヒットストップ時間
	Scale = { 50.0f,50.0f,0.0f };	// 画像の大きさ
	Move = 1;

	// 位置の設定
	{
		p_transform->scale = Scale;
		p_transform->position = { 0.0f,0.0f, -2.0f };
	}

	// レンダラーの設定
	const char* biteenemyTexName = "Assets/01-Texture/99-Test/daruma.jpg";
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(biteenemyTexName);

	//アニメーターの設定
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(2, 3));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();


	//animationの設定
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


	// 本体のコライダーの設定
	bodyCollider = AddComponent<BoxCollider2D>();
	bodyCollider->SetIsActive(true);

	//攻撃のコライダーの設定
	AttackCollider = AddComponent<BoxCollider2D>();
	AttackCollider->SetOffset({ -50.f,0.0f,0.0f });
	AttackCollider->SetIsActive(false);

	std::cout << "BiteEnemyパラメータ完了\n";
}

void BiteEnemy::Bite_Update()
{
	// 時間更新
	timer++;
	
	switch (GetAct())
	{
	case 0:
		Normal_Move();
		break;
	case 1:
		Attack_Move();
		break;
	case 2:
		Spin_Move();
		break;
	case 3:
		Dead_Move();
		break;
	}
}

// アニメーション
void BiteEnemy::Bite_Animation()
{
	// 状態で分ける
	switch (GetAct())
	{
	case 0:
		Normal_Animation();
		break;
	case 1:
		Attack_Animation();
		break;
	case 2:
		Spin_Animation();
		break;
	case 3:
		Dead_Animation();
		break;
	}
}

//====================================================================================================
// 状態
// ===================================================================================================
// 通常状態の挙動
void BiteEnemy::Normal_Move()
{
	// 決められたフレーム時間経過すれば行動変化
	if (Active[GetMove()] <= timer)
	{
		timer = 0;
		// 次の挙動へ
		AddMove();
	}
}

// 攻撃状態の挙動
void BiteEnemy::Attack_Move()
{
	// 攻撃判定を出す
	if (timer == 1){SetAColliderActive(true);}
	if (Active[GetMove()] <= timer)
	{
		timer = 0;
		// 攻撃判定を消す
		SetAColliderActive(false);
		// 次の挙動へ
		AddMove();
	}
}

// 回転状態の挙動
void BiteEnemy::Spin_Move()
{
	if (Active[GetMove()] <= timer)
	{
		timer = 0;
		// 向きを更新
		AddDirection();
		// 攻撃判定の位置変更
		SetAColliderPos();
		// 次の挙動へ
		AddMove();
	}
}

// 回転状態の挙動
void BiteEnemy::Dead_Move()
{
	if(timer == 1)
	{
		// 自身の当たり判定の削除
		bodyCollider->GetIsActive();
	}
	if (Active[GetMove()] <= timer)
	{
		timer = 0;
		// 描写を削除
		//GetComponent<SpriteRenderer>()->SetIsActive(false);
		// エネミーの総数の減少
		DownEnemyCount();
		std::cout << "エラー\n";
	}
}


//==============================================================================================
// 判定
//==============================================================================================
// 本体判定を適応するか否か
void BiteEnemy::SetIColliderActive(bool NewActive)
{
	bodyCollider->SetIsActive(NewActive);

	if (bodyCollider->GetIsActive() == true)
	{
		std::cout << "コライダー実行中\n";
	}
	else
	{
		std::cout << "コライダー非実行中\n";
	}
}

// 攻撃判定を適応するか否か
void BiteEnemy::SetAColliderActive(bool NewActive)
{
	
	AttackCollider->SetIsActive(NewActive);

	if (AttackCollider->GetIsActive() == true)
	{
		std::cout << "コライダー実行中\n";
	}
	else
	{
		std::cout << "コライダー非実行中\n";
	}
}

// 攻撃判定の位置変更
void BiteEnemy::SetAColliderPos()
{
	const int dir = GetDirection();	// 向きを取得
	if (dir == 0) { AttackCollider->SetOffset({ -50.0f,0.0f,0.0f }); }
	else if(dir==1){ AttackCollider->SetOffset({ 0.0f,50.0f,0.0f }); }
	else if(dir==2){ AttackCollider->SetOffset({ 50.0f,0.0f,0.0f }); }
	else if(dir==3){ AttackCollider->SetOffset({ 0.0f,-50.0f,0.0f }); }
	else { std::cout << "攻撃方向のエラー\n"; }
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
	if (col->GetTag()=="a")
	{
		//DeadMove();
	}
}


//========================================================================================
//アニメーション
//========================================================================================
// 通常状態のアニメーション
void BiteEnemy::Normal_Animation()
{
	// 更新
}

// 攻撃状態のアニメーション
void BiteEnemy::Attack_Animation()
{
	// 更新
}

// 回転状態のアニメーション
void BiteEnemy::Spin_Animation()
{
	// 更新
}

// 死亡状態のアニメーション
void BiteEnemy::Dead_Animation()
{
	// 更新
}