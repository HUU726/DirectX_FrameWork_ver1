#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#include"BiteEnemy.h"

BiteEnemy::BiteEnemy()
{
	AddEnemyCount();	// エネミーの総数
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

void BiteEnemy::InitParam()
{
	const char* biteenemyTexName = "Assets/01-Texture/99-Test/daruma.jpg";

	hitstopspead = 1.0f;
	hitstoptime = 10.0f;
	Scale = { 50.0f,50.0f,0.0f };
	timer = 0;

	Idle_flame;

	/*
	// 敵の情報
	float hitstopspeed;	// HPが0になった際に止まる時間のスピード
	float hitstoptime;	// ヒットストップがかかるフレーム数
	hft::HFFLOAT3 Scale;	// 噛みつく敵の画像のサイズ
	GameObject2D object2D;	// 本体のアニメーション
	int Move[4];	// 行動ルーチン

	// 経過時間 
	int timer;

	// 状態別のフレーム数
	int Idle_1_flame;
	int Idle_2_flame;
	int Attack_flame;
	int Spin_flame;
	int Dead_flame;
	*/
}