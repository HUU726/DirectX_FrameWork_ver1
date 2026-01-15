#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#include"BiteEnemy.h"



BiteEnemy::BiteEnemy()
{
	//AddEnemyCount();	// エネミーの総数追加
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

	hitstopspead = 1.0f;	// ヒットストップスピード(現在は等速)
	hitstoptime = 10.0f;	// ヒットストップ時間
	Scale = { 50.0f,50.0f,0.0f };	// 画像の大きさ
	timer = 0;						// 経過フレーム
	Idle_1_flame = 30;				// 通常状態のかかるフレーム(30F)
	Idle_2_flame = 20;				// 通常状態のかかるフレーム(20F)
	Attack_flame = 20;				// 攻撃状態のかかるフレーム(20F)
	Spin_flame = 3;					// 回転状態のかかるフレーム(3F)
	Dead_flame = 20;				// 死亡状態のかかるフレーム(20F)
}