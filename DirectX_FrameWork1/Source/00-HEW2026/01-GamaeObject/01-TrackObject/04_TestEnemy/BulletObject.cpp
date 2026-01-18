#include"BulletObject.h"

#include"../../../10-Map/00-BaseMap/BaseMap.h"
#include "../../../../01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

class BaseMap;

BulletObject::BulletObject(const hft::HFFLOAT3& NewPosition,const hft::HFFLOAT2& NewAngle)
{
	// 座標、方向を指定された数値で初期化
	// 座標の情報
	p_transform->position = NewPosition;
	
	// 方向の情報
	const hft::HFFLOAT2 LIGHT = { 1,0 };
	const hft::HFFLOAT2 UP = { 1,0 };
	const hft::HFFLOAT2 LEFT = { -1,0 };
	const hft::HFFLOAT2 DOWN = { 0,-1 };

	if (GetAngle() == LIGHT) { SetDirection(0);}
	else if (GetAngle() == UP) { SetDirection(1); }
	else if (GetAngle() == LEFT) { SetDirection(2); }
	else if (GetAngle() == DOWN) { SetDirection(3); }
	else { std::cout << "エラー\n"; }
}

void BulletObject::Init()
{
	// パラメータ初期化;

	// 当たり判定初期化
	bodyColler = AddComponent<BoxCollider2D>();

	// アニメーター初期化
	//画像の設定
	{
		//レンダラーの設定
		bodyObj.GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/daruma.jpg");

		//アニメーターの設定
		SpriteAnimator* p_spriteAnimator = bodyObj.AddComponent<SpriteAnimator>(hft::HFFLOAT2(3, 3));
		hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

		//animationの設定
		// 通常
		SpriteAnimation anim1(div, { 0,0 }, 9);
		anim1.Active();
		anim1.SetID(0);

		anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim1.SetPriority(0);
		float flame = 10;

		for (int i = 0; i < 9; i++)
		{
			anim1.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim1);

		// 破裂
		SpriteAnimation anim2(div, { 0,0 }, 9);
		anim2.Active();
		anim2.SetID(1);

		anim2.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim2.SetPriority(0);
		flame = 10;

		for (int i = 0; i < 9; i++)
		{
			anim2.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim2);

	}
}

void BulletObject::Update()
{
	timer++;

	switch (currentState)
	{
	case State::defoult:
		Defoult();
		break;
	case State::blast:
		Blast();
		break;
	}
}

void BulletObject::Defoult()
{
	// 経過時間が存在時間を超えているとき、blastへ移行
	if (timer >= livetime)
	{
		currentState = State::blast;
	}

	// 座標加算
	UpdatePos();
	CheakMyPos();

	// アニメーションを再生
}

void BulletObject::Blast()
{
	// 当たり判定を消去
	p_transform->SetIsActive(false);

	// アニメーションを再生

}


//===============================================================================================
void BulletObject::UpdatePos()
{
	const hft::HFFLOAT3 NowPos = p_transform->position;

	if (GetDirection() == 0) { p_transform->position = NowPos.x + spead * 1.0f; }
	else if(GetDirection() == 1){ p_transform->position = NowPos.y + spead * 1.0f; }
	else if (GetDirection() == 2) { p_transform->position = NowPos.x - spead * 1.0f; }
	else if (GetDirection() == 3) { p_transform->position = NowPos.y - spead * 1.0f; }
	else { std::cout << "エラー\n"; }
}

void BulletObject::CheakMyPos()
{
	hft::HFFLOAT2 LeftTop = GetComponent<BaseMap>()->GetLefTopPos();
	hft::HFFLOAT2 RightBottom = GetComponent<BaseMap>()->GetRitBotPos();

	if (LeftTop.x > p_transform->position.x) { p_transform->position.x = RightBottom.x; }
	else if (LeftTop.y < p_transform->position.y) { p_transform->position.y = RightBottom.y; }
	else if (RightBottom.x < p_transform->position.x) { p_transform->position.x = LeftTop.x; }
	else if (RightBottom.y > p_transform->position.y) { p_transform->position.y = LeftTop.y; }
}

void BulletObject::OnCollisionEnter(Collider* _p_col)
{
	// 対象のオブジェクトにヒットした際、blastに移行
	//	currentState = blast;
}