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
	//パラメータの設定
	isAttack = ThormObjectParam::isAttack;
	timer = 0;
	attackTime = ThormObjectParam::animationTime;
	defaultTime = ThormObjectParam::defaultTime;
	animationTime = ThormObjectParam::animationTime;


	//本体オブジェクトの設定
	//位置の設定
	p_transform->position = hft::HFFLOAT3{ 0.f,0.f, 0.f };
	p_transform->scale = hft::HFFLOAT3{ 150.f,150.f,1 };

	//レンダラーの設定
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/AnimationTestver2.png");

	//アニメーターの設定
	//画像の分割数を設定
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(3, 3));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	//animationの設定
	SpriteAnimation anim(div, { 0,0 }, 9);
	anim.Active();
	anim.SetID(0);

	anim.SetType(SPRITE_ANIM_TYPE::LOOP);
	anim.SetPriority(0);
	float flame = 10;

	for (int i = 0; i < 9; i++)
	{
		anim.GetCellRef(i).flame = flame;
	}


	p_spriteAnimator->AddAnimation(anim);


	//コライダーの設定
	AddComponent<BoxCollider2D>();


	//影オブジェクトの設定

}


void ThormObject::Update()
{
	//経過フレームを計る
	timer++;

	//攻撃状態かどうか
	if (isAttack)
	{
		AttackMove();
	}
	else
	{
		DefaultMove();
	}

	//アニメーションは攻撃状態に関わらず一定周期で行う
	Animation();


}

void ThormObject::Animation()
{
	//影側のアニメーション
	SpriteAnimator* animator = GetComponent<SpriteAnimator>();

	animator->Play(0);
}

void ThormObject::SetColliderActive(bool state)
{
	BoxCollider2D* ptr_boxColl2d = GetComponent<BoxCollider2D>();
	ptr_boxColl2d->SetIsActive(state);
}

void ThormObject::DefaultMove()
{
	//攻撃状態に切り替える処理
	if (defaultTime <= timer)
	{
		SetColliderActive(true);
		isAttack = true;
		timer = 0;
		std::cout << "攻撃モードに切り替え" << std::endl;
	}
}

void ThormObject::AttackMove()
{
	//通常状態に切り替える処理
	if (attackTime <= timer)
	{
		SetColliderActive(false);
		isAttack = false;
		timer = 0;
		std::cout << "通常モードに切り替え" << std::endl;
	}
}
