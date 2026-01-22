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

	//本体部のコライダー設定
	bodyColl = AddComponent<BoxCollider2D>();
	bodyColl->SetSize({ 80.f, 80.f, 1.f });
	bodyColl->SetIsActive(false);

	//テクスチャ
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/03-Enemy/EnemyBom.png");

	//本体のアニメーション設定
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(8, 8));

	//立ち状態のアニメーション
	{
		hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();
		SpriteAnimation anim(div, { 0,0 }, 7);

		anim.SetID(0);
		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim.SetPriority(0);

		float flame = 10;

		for (int i = 0; i < 7; i++)
		{
			anim.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim);
	}

	//溜めのアニメーション
	{
		hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();
		SpriteAnimation anim(div, { 4, 1 }, 2);

		anim.SetID(1);
		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim.SetPriority(1);

		float flame = 14;

		for (int i = 0; i < 2; i++)
		{
			anim.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim);

		//p_spriteAnimator->Play(BomState::blastWait);
	}

	//爆発時のアニメーション
	{
		hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();
		SpriteAnimation anim(div, { 7, 1 }, 7);

		anim.SetID(2);
		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim.SetPriority(2);

		float flame = 14;

		for (int i = 0; i < 7; i++)
		{
			anim.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim);

		//p_spriteAnimator->Play(BomState::blast);
	}


	//検査オブジェクト用のデータ
	{
		//画像表示用のオブジェクトの初期値

		//レンダラー設定
		searchRenderer = new GameObject2D;
		searchRenderer->GetTransformPtr()->scale = { 280.f, 280.f, 1.f };
		searchRenderer->GetTransformPtr()->position.z = -4;
		searchRenderer->SetIsRender(false);

		SpriteRenderer* renderer = searchRenderer->GetComponent<SpriteRenderer>();
		renderer->LoadTexture("Assets/01-Texture/99-Test/daruma.jpg");

		//コライダー設定
		searchColl = AddComponent<BoxCollider2D>();
		searchColl->SetSize({ 280.f, 280.f, 1.f });
		searchColl->SetIsActive(true);
	}



	//爆風判定用のオブジェクトの初期設定
	{
		for (int i = 0; i < 8; i++)
		{
			GameObject2D* bomAttack = new GameObject2D;
			bomAttack->Init();
			bomAttack->SetTag("Enemy");
			bomAttack->GetTransformPtr()->scale = { 80.f, 80.f, 1.f };
			bomAttack->SetIsRender(false);

			BoxCollider2D* coll = bomAttack->AddComponent<BoxCollider2D>();
			coll->SetSize({ 80.f, 80.f, 1.f });
			coll->SetIsActive(false);

			SpriteRenderer* renderer = bomAttack->GetComponent<SpriteRenderer>();
			std::shared_ptr<Texture> tex = renderer->LoadTexture("Assets/01-Texture/03-Enemy/EnemyBom.png");

			
			SpriteAnimator* p_spriteAnimator = bomAttack->AddComponent<SpriteAnimator>(hft::HFFLOAT2(8, 8));

			hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();
			SpriteAnimation anim(div, { 4, 2 }, 2);

			anim.SetID(1);
			anim.SetType(SPRITE_ANIM_TYPE::LOOP);
			anim.SetPriority(1);

			float flame = 7;

			for (int i = 0; i < 2; i++)
			{
				anim.GetCellRef(i).flame = flame;
			}

			p_spriteAnimator->AddAnimation(anim);



			bomAttackArray.push_back(bomAttack);
		}
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
	OffSetBlastPosition();
}

void BombEnemy::Stand()
{
	searchColl->SetIsActive(true);

	bodyColl->SetIsActive(true);

	ChangeBlastActiveState(false);

	//立ちアニメーションを再生
	GetComponent<SpriteAnimator>()->Play(BomState::stand);


	//検査用オブジェクトの座標を本体に合わせる
	searchRenderer->GetTransformPtr()->position = p_transform->position;

	//爆風オブジェクトの座標を本体に合わせる
	OffSetBlastPosition();
}

void BombEnemy::BlastWait()
{
	timer++;

	searchColl->SetIsActive(false);
	searchRenderer->SetIsRender(false);

	bodyColl->SetIsActive(false);

	//溜めアニメーションを再生
	GetComponent<SpriteAnimator>()->Stop(BomState::stand);
	GetComponent<SpriteAnimator>()->Play(BomState::blastWait);


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

	ChangeBlastActiveState(true);

	//爆破アニメーションを再生
	GetComponent<SpriteAnimator>()->Stop(BomState::blastWait);
	GetComponent<SpriteAnimator>()->Play(BomState::blast);
	
	//周りの爆風アニメーション再生
	BlastAnimation();

	//一定時間後に死亡状態に移行
	if (timer >= blastTime)
	{

		timer = 0;

		currentState = BomState::dead;

	}
}

void BombEnemy::Dead()
{
	bodyColl->SetIsActive(false);

	ChangeBlastActiveState(false);


	//自身のコンポーネントを消す
	GetComponent<SpriteRenderer>()->SetIsActive(false);
	SetIsRender(false);

}

void BombEnemy::BlastAnimation()
{
	for (auto& bomAttack : bomAttackArray)
	{
		bomAttack->GetComponent<SpriteAnimator>()->Play(0);
	}
}

void BombEnemy::OffSetBlastPosition()
{
	float offSetValue = 80;
	hft::HFFLOAT3 offSetUp	  = {  0.f, offSetValue, 0.f};
	hft::HFFLOAT3 offSetDown  = {  0.f, -offSetValue, 0.f};
	hft::HFFLOAT3 offSetLeft  = { -offSetValue, 0.f, 0.f};
	hft::HFFLOAT3 offSetRight = {  offSetValue, 0.f, 0.f};
	
	hft::HFFLOAT3 bodyPos = p_transform->position;

	bomAttackArray[0]->GetTransformPtr()->position = bodyPos + offSetUp + offSetLeft;
	bomAttackArray[1]->GetTransformPtr()->position = bodyPos + offSetUp;
	bomAttackArray[2]->GetTransformPtr()->position = bodyPos + offSetUp + offSetRight;
	bomAttackArray[3]->GetTransformPtr()->position = bodyPos + offSetLeft;
	bomAttackArray[4]->GetTransformPtr()->position = bodyPos + offSetRight;
	bomAttackArray[5]->GetTransformPtr()->position = bodyPos + offSetDown + offSetLeft;
	bomAttackArray[6]->GetTransformPtr()->position = bodyPos + offSetDown;
	bomAttackArray[7]->GetTransformPtr()->position = bodyPos + offSetDown + offSetRight;
}

void BombEnemy::ChangeBlastActiveState(bool state)
{
	for (auto& bomAttack : bomAttackArray)
	{
		bomAttack->SetIsActive(state);
		bomAttack->SetIsRender(state);
	}
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
