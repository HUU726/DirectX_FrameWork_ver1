#include "ThormObject.h"
#include "ThormObjectParam.h"	//トゲオブジェクトのパラメータ

#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"



ThormObject::ThormObject()
{

}

ThormObject::~ThormObject()
{

}

void ThormObject::Init()
{
	//タイマーを初期化
	timer = 0;

	//影のパラメータの設定
	{
		currentState = State::Default;
		attackTime = ThormObjectParam::attackTime;
		fallTime = ThormObjectParam::fallTime;
		defaultTime = ThormObjectParam::defaultTime;

		//位置の設定
		p_transform->scale = ThormObjectParam::shadowInitialScale;

		//レンダラーの設定
		std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(ThormObjectParam::shadowTexName);

		//アニメーターの設定
		SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(1, 1));
		hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

		//animationの設定
		SpriteAnimation anim(div, { 0,0 }, 1);
		anim.Active();
		anim.SetID(0);

		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim.SetPriority(0);
		float flame = 10;

		for (int i = 0; i < 1; i++)
		{
			anim.GetCellRef(i).flame = flame;
		}


		p_spriteAnimator->AddAnimation(anim);


		//コライダーの設定
		BoxCollider2D* box2d =  AddComponent<BoxCollider2D>();
		box2d->SetIsActive(false);
	}

	//トゲのパラメータの設定
	{
		thormFallSpeed = 0;
		distanceHold = ThormObjectParam::distanceHold;
		scaleDownSpeed = ThormObjectParam::scaleDownSpeed;
		thormFallWaitTime = ThormObjectParam::thormFallWaitTime;
		thormFallAcceleration = ThormObjectParam::thormFallAcceleration;
		initialOffset = ThormObjectParam::thormIntialOffset;
		initialScale = ThormObjectParam::thormInitialScale;

		//座標の設定
		{
			Transform* bodyTrf = mainBodyObj.GetComponent<Transform>();
			Transform shadowTrf = GetTransform();
			bodyTrf->position = shadowTrf.position + initialOffset;
			bodyTrf->scale = initialScale;
		}

		//画像の設定
		{
			//レンダラーの設定
			mainBodyObj.GetComponent<SpriteRenderer>()->LoadTexture(ThormObjectParam::thormTexName);

			////アニメーターの設定
			//SpriteAnimator* p_spriteAnimator = mainBodyObj.AddComponent<SpriteAnimator>(hft::HFFLOAT2(3, 3));
			//hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

			////animationの設定
			//SpriteAnimation anim(div, { 0,0 }, 9);
			//anim.Active();
			//anim.SetID(0);

			//anim.SetType(SPRITE_ANIM_TYPE::LOOP);
			//anim.SetPriority(0);
			//float flame = 10;

			//for (int i = 0; i < 9; i++)
			//{
			//	anim.GetCellRef(i).flame = flame;
			//}


			//p_spriteAnimator->AddAnimation(anim);
		}
	}
}


void ThormObject::Update()
{
	ShadowUpdate();					//影の部分の更新
	ThormAnimation(currentState);	//アニメーション
}

void ThormObject::ShadowUpdate()
{
	//現在の状態からの経過フレームを計る
	timer++;

	switch (currentState)
	{
	case State::Default:
		DefaultMove();
		break;
	case State::Falling:
		FallingMove();
		break;
	case State::Attack:
		AttackMove();
		break;
	default:
		break;
	}
}


void ThormObject::ThormAnimation(const State state)
{
	Transform* bodyTrf = mainBodyObj.GetTransformPtr();
	Transform shadowTrf = GetTransform();

	if (state == Default)
	{
		//通常状態の時は画像非表示、落下速度、座標、拡大率を初期値にリセット
		thormFallSpeed = 0;
		bodyTrf->position = shadowTrf.position + initialOffset;
		bodyTrf->scale = initialScale;
		mainBodyObj.SetIsRender(false);
		std::cout << "トゲが落下モードに切り替え" << std::endl;
	}
	else if(state == Falling)
	{
		//現在の距離を測定
		hft::HFFLOAT3 diff = bodyTrf->position - shadowTrf.position;
		float currentDistance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
		
		//一定距離内まで落ちていたら拡大率を0にする
		if (currentDistance <= distanceHold)
		{
			bodyTrf->scale = { 0.f, 0.f, 1.f };
			return;
		}

		//まだ離れて居たら、落下速度を上げる
		thormFallSpeed += thormFallAcceleration;

		//現在の落下スピードに基づき トゲの座標を降下
		bodyTrf->position.y += thormFallSpeed;

		//拡大率を縮小
		bodyTrf->scale -= hft::HFFLOAT3(scaleDownSpeed, scaleDownSpeed, 1.f);

		//画像を描画する
		mainBodyObj.SetIsRender(true);
	}
	else if(state == Attack)
	{
		//攻撃状態になったらスケールを変更する
		bodyTrf->scale = { 0.f, 0.f, 1.f };

		SpriteAnimator* anim = GetComponent<SpriteAnimator>();
		anim->Stop(0);

		//画像を描画する
		mainBodyObj.SetIsRender(true);
	}
}

void ThormObject::SetColliderActive(bool state)
{
	BoxCollider2D* ptr_boxColl2d = GetComponent<BoxCollider2D>();
	ptr_boxColl2d->SetIsActive(state);

	if (ptr_boxColl2d->GetIsActive())
	{
		std::cout << "コライダーON" << std::endl;
	}
	else
	{
		std::cout << "コライダーOFF" << std::endl;
	}
}

void ThormObject::DefaultMove()
{
	//攻撃状態に切り替える処理
	if (defaultTime <= timer)
	{
		currentState = State::Falling;
		timer = 0;
	}
}

void ThormObject::FallingMove()
{
	if (fallTime <= timer)
	{
		SetColliderActive(true);
		currentState = State::Attack;
		timer = 0;
	}
}

void ThormObject::AttackMove()
{
	//通常状態に切り替える処理
	if (attackTime <= timer)
	{
		SetColliderActive(false);
		currentState = State::Default;
		timer = 0;
	}
}
