#include "ThormObject.h"

ThormObject::ThormObject()
{
	
}

ThormObject::~ThormObject()
{

}

void ThormObject::Init()
{
	//オブジェクトのid設定
	id = 2;
	//name = "ThormObject";
	//tag = "Enemy";

	GetComponent<Transform>()->position = hft::HFFLOAT3{-300.f, 200.f, 5.f};


	//マップの何処に配置するか設定
	hft::HFFLOAT2 index(0.0f, 0.0f);
	SetLineIndex({ 0.f, 0.f });


	//ボックスコライダーの設定============================
	BoxCollider2D* ptr_boxColl2d = AddComponent<BoxCollider2D>();
	ptr_boxColl2d->SetGameObject((GameObject*)this);
	ptr_boxColl2d->SetSize({ 100.f, 100.0f, 0.f });
	//ボックスコライダーの設定============================


	//スプライトレンダラーの設定==========================
	SpriteRenderer* renderer = GetComponent<SpriteRenderer>();
	renderer->LoadTexture("Assets/01-Texture/99-Test/wave.png");



	//アニメーターの設定============================
	//SpriteAnimator* ptr_animator = AddComponent<SpriteAnimator>();
	//ptr_animator->SetGameObject((GameObject*)this);

	////アニメーションの設定
	//SpriteAnimation anim01;
	//anim01.SetID(0);
	//anim01.SetType(SPRITE_ANIM_TYPE::LOOP);
	//anim01.SetPriority(0);
	//anim01.Active();

	////セルの設定
	//SpriteAnimationCell cell0(20, { 0.2f, 0.f });
	//SpriteAnimationCell cell1(20, { 0.4f, 0.f });
	//SpriteAnimationCell cell2(20, { 0.6f, 0.f });
	//SpriteAnimationCell cell3(20, { 0.8f, 0.f });

	//anim01.AddCell(cell0);
	//anim01.AddCell(cell1);
	//anim01.AddCell(cell2);
	//anim01.AddCell(cell3);

	//ptr_animator->AddAnimation(anim01);
	//アニメーターの設定終了============================
}

void ThormObject::Update()
{
	timer++;

	if (isAttack == false)
	{
		DefaultMove();
	}
	else
	{
		AttackMove();
	}

	Animation();


}

void ThormObject::Animation()
{
	/*if (ptr_animator)
	{
		ptr_animator->Update();
	}*/
}

void ThormObject::SetColliderActive(bool state)
{
	BoxCollider2D* ptr_boxColl2d = AddComponent<BoxCollider2D>();
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
		SetColliderActive(true);
		isAttack = false;
		timer = 0;
		std::cout << "通常モードに切り替え" << std::endl;
	}
}
