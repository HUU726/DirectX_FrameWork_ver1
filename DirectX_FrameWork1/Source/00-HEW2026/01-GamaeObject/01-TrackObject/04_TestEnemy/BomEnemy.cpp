#include "BomEnemy.h"

#include "../../../../99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

void BomEnemy::Init()
{
	bodyColl = AddComponent<BoxCollider2D>();
	bodyColl->SetSize( { 80.f, 80.f, 1.f } );


	searchColl = AddComponent<BoxCollider2D>();
	searchColl->SetSize({ 280.f, 280.f, 1.f });

	bomColl    = AddComponent<BoxCollider2D>();
	bomColl->SetSize({ 280.f, 280.f, 1.f });
}

void BomEnemy::Update()
{
	timer++;

	switch (currentState)
	{
	case BomEnemy::stand:
		Stand();
		break;
	case BomEnemy::blastWait:
		BlastWait();
		break;
	case BomEnemy::blast:
		Blast();
		break;

	case BomEnemy::dead:
		Dead();
		break;

	default:
		break;
	}
}

void BomEnemy::Stand()
{
	if (isBlast)
	{
		timer = 0;
		currentState = BomEnemy::blastWait;
	}
}

void BomEnemy::BlastWait()
{
	if (timer >= blastWaitTime)
	{
		timer = 0;
		currentState = BomEnemy:: blast;
	}
}

void BomEnemy::Blast()
{
	if (timer >= blastTime)
	{
		timer = 0;
		currentState = BomEnemy::dead;
	}
}

void BomEnemy::Dead()
{
	//描画OFF、自身のコンポーネント全て非アクティブ化
}

void BomEnemy::OnCollisionEnter(Collider* _p_col)
{
	//接触相手が自分以外のオブジェクト、連結オブジェクトじゃない場合壊す
	//連結ブロックの攻撃判定落下トゲ 爆弾 弾 爆弾の爆風
	

}

void BomEnemy::OnCollisionExit(Collider* _p_col)
{

}

void BomEnemy::OnCollisionStay(Collider* _p_col)
{

}