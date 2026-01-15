#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#include"BiteEnemy.h"


BiteEnemy::BiteEnemy()
{
	InitParam();	// エネミーのパラメータの初期化
}

BiteEnemy::~BiteEnemy()
{

}

// 初期化=============================================================
void BiteEnemy::Init()
{

}

// 更新===============================================================
void BiteEnemy::Update()
{

}

// パラメータ初期化============================================================
void BiteEnemy::InitParam()
{
	// タイマーの初期化
	timer = 0;

	// 画像の読み込み
	const char* biteenemyTexName = "Assets/01-Texture/99-Test/daruma.jpg";

	// 本体
	{
		hitstopspead = 1.0f;	// ヒットストップスピード(現在は等速)
		hitstoptime = 10.0f;	// ヒットストップ時間
		Scale = { 50.0f,50.0f,0.0f };	// 画像の大きさ
		Move = 0;

		//コライダーの設定
		BoxCollider2D* boxI2d = AddComponent<BoxCollider2D>();
		boxI2d->SetIsActive(true);
	}

	// 攻撃マス
	{

		//コライダーの設定
		BoxCollider2D* boxA2d = AddComponent<BoxCollider2D>();
		boxA2d->SetIsActive(false);
	}
	

	std::cout << "BiteEnemyパラメータ完了\n";
}

void BiteEnemy::Bite_Test_Update()
{
	Bite_Update();				// 本体の更新
	Bite_Animation(GetState());	// アニメーションの更新
}

void BiteEnemy::Bite_Update()
{
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

void BiteEnemy::Normal_Move()
{
	if (Active[GetMove()] <= timer)
	{
		SetState(0);
		timer = 0;
		AddMove();
	}
}

void BiteEnemy::Attack_Move()
{
	if (time == 0)
	{
		// 攻撃判定の適用
		SetAColliderActive(true);
	}
	if (Active[GetMove()] <= timer)
	{
		SetState(1);
		// 攻撃判定の消去
		SetAColliderActive(false);
		timer = 0;
		AddMove();
	}
}

void BiteEnemy::Spin_Move()
{
	if (Active[GetMove()] <= timer)
	{
		SetState(2);
		timer = 0;
		AddMove();
	}
}

void BiteEnemy::Dead_Move()
{
	if (Active[GetMove()] <= timer)
	{
		timer = 0;
		delete this;
	}
}

// アニメーション
void BiteEnemy::Bite_Animation(const int& state)
{
	// 状態で分ける
	switch (state)
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

// 攻撃判定を適応するか否か
void BiteEnemy::SetAColliderActive(bool NewActive)
{
	BoxCollider2D* ptr = GetComponent<BoxCollider2D>();
	ptr->SetIsActive(NewActive);

	if (ptr->GetIsActive() == true)
	{
		std::cout << "コライダー実行中\n";
	}
	else
	{
		std::cout << "コライダー非実行中\n";
	}
}