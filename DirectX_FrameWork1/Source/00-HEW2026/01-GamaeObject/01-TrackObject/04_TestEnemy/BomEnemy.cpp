#include "BomEnemy.h"

#include "../03_ConnectObject/ConnectObject.h"

#include "../../../../99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"


void BombEnemy::Init()
{
	//自身のタグ設定
	tag = "Bom";

	//サイズ設定
	p_transform->scale = { 80.f, 80.f, 1.f };

	//体のコライダー設定
	bodyColl = AddComponent<BoxCollider2D>();
	bodyColl->SetSize({ 80.f, 80.f, 1.f });
	bodyColl->SetIsActive(false);

	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/daruma.jpg");

	{

		SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(3, 3));

		hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

		{

			SpriteAnimation anim(div, { 0,0 }, 9);

			anim.SetID(0);

			anim.SetType(SPRITE_ANIM_TYPE::LOOP);

			anim.SetPriority(0);

			float flame = 60;

			for (int i = 0; i < 9; i++)

			{

				anim.GetCellRef(i).flame = flame;

			}

			p_spriteAnimator->AddAnimation(anim);

		}

	}


	//検査用のデータ

	{
		//画像表示用のオブジェクトの初期値

		searchRenderer = new GameObject2D;

		searchRenderer->SetIsRender(true);

		searchRenderer->GetTransformPtr()->scale = { 280.f, 280.f, 1.f };

		searchRenderer->GetTransformPtr()->position.z = -4;

		SpriteRenderer* renderer = searchRenderer->AddComponent<SpriteRenderer>();

		renderer->LoadTexture("Assets/01-Texture/99-Test/daruma.jpg");

		searchColl = AddComponent<BoxCollider2D>();

		searchColl->SetSize({ 280.f, 280.f, 1.f });

		searchColl->SetIsActive(true);

	}


	//爆風判定用のオブジェクトの初期設定
	{
		bomAttack = new GameObject2D;
		bomAttack->Init();
		bomAttack->SetTag("Enemy");
		//bomAttack->SetIsRender(true);
		bomAttack->GetTransformPtr()->scale = { 280.f, 280.f, 1.f };
		bomAttack->GetTransformPtr()->scale = { 280.f, 280.f, 1.f };


		BoxCollider2D* coll = bomAttack->AddComponent<BoxCollider2D>();
		coll->SetSize({ 280.f, 280.f, 1.f });
		coll->SetIsActive(false);

		SpriteRenderer* renderer = bomAttack->AddComponent<SpriteRenderer>();
		std::shared_ptr<Texture> tex = renderer->LoadTexture("Assets/01-Texture/03-Enemy/EnemyBom.png");
	}
}

void BombEnemy::Update()
{

	//現在の状態ごとに処理切り替え
	switch (currentState)
	{

	case BomState::stand:

		Stand();

		break;

	case BomState::blastWait:

		BlastWait();

		break;

	case BomState::blast:

		Blast();

		break;

	case BomState::dead:

		Dead();

		break;

	default:
		break;

	}

	//爆破用オブジェクトの座標を本体に合わせる
	bomAttack->GetTransformPtr()->position = p_transform->position;
}

void BombEnemy::Stand()
{
	searchColl->SetIsActive(true);

	bodyColl->SetIsActive(true);

	bomAttack->GetComponent<BoxCollider2D>()->SetIsActive(false);


	//検査用オブジェクトの座標を本体に合わせる
	searchRenderer->GetTransformPtr()->position = p_transform->position;
}

void BombEnemy::BlastWait()
{
	timer++;

	searchColl->SetIsActive(false);

	searchRenderer->SetIsRender(false);

	bodyColl->SetIsActive(false);

	bomAttack->GetComponent<BoxCollider2D>()->SetIsActive(false);

	//一定時間後に爆発状態に移行
	if (timer >= blastWaitTime)
	{
		timer = 0;
		currentState = BomState::blast;
	}
}

void BombEnemy::Blast()
{

	timer++;

	//検査用オブジェクトを非アクティブ

	searchColl->SetIsActive(false);

	bodyColl->SetIsActive(false);

	bomAttack->GetComponent<BoxCollider2D>()->SetIsActive(true);
	bomAttack->SetIsRender(true);


	//一定時間後に死亡状態に移行
	if (timer >= blastTime)
	{

		timer = 0;

		currentState = BomState::dead;

	}
}

void BombEnemy::Dead()
{
	//描画OFF、自身のコンポーネント全て非アクティブ化

	bodyColl->SetIsActive(false);

	bomAttack->GetComponent<BoxCollider2D>()->SetIsActive(false);
	bomAttack->SetIsRender(true);


	//自身のコンポーネントを消す
	GetComponent<SpriteRenderer>()->SetIsActive(false);
	SetIsRender(false);

}


void BombEnemy::OnCollisionEnter(Collider* _p_col)

{

	//接続先のオブジェクトを確認

	GameObject* obj = _p_col->GetGameObject();

	//接続先が存在するか

	if (!obj)

	{

		return;

	}

	//接続先が自身と同じ場合何もしない

	if (obj == this)

	{

		return;

	}

	//爆弾の場合何もしない　爆風は普通のゲームオブジェクトとして扱う

	if (auto* co = dynamic_cast<BombEnemy*>(obj))

	{

		return;

	}


	//連結オブジェクトの場合何もしない

	if (auto* co = dynamic_cast<ConnectObject*>(obj))

	{

		return;

	}


	//普通のゲームオブジェクト2Dだった場合（爆風、連結オブジェクトの間、弾,トゲ等）

	if (obj && currentState == stand)

	{

		currentState = BomState::blastWait;

	}

}


void BombEnemy::OnCollisionExit(Collider* _p_col)

{

}

void BombEnemy::OnCollisionStay(Collider* _p_col)

{

}
