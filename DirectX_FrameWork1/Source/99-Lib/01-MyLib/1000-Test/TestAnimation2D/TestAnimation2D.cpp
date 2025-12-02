#include "TestAnimation2D.h"

#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"

enum TEST_ANIM_ID
{
	WAIT = 0,
	JUMP = 1,
	RUN = 2,
};

void TestAnimation2D::Init()
{
	GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/AnimationTest.png");
	SpriteAnimator* animator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(4, 4));
	hft::HFFLOAT2 div = animator->GetDivision();
	{
		SpriteAnimation anim(div, { 0,0 }, 5);
		anim.SetID(TEST_ANIM_ID::WAIT);
		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim.SetPriority(0);
		float flame = 40;

		for ( int i = 0; i < 5; i++ )
			anim.GetCellRef(i).flame = flame;

		animator->AddAnimation(anim);
	}
	{
		SpriteAnimation anim(div, { 1,1 }, 4);
		anim.SetID(TEST_ANIM_ID::JUMP);
		anim.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim.SetPriority(1);
		float flame(30);
		for ( int i = 0; i < 4; i++ )
			anim.GetCellRef(i).flame = flame;

		animator->AddAnimation(anim);
	}
	{
		SpriteAnimation anim(div, { 2,1 }, 7);
		anim.SetID(TEST_ANIM_ID::RUN);
		anim.SetType(SPRITE_ANIM_TYPE::BOOMERANG);
		anim.SetPriority(2);
		float flame = 15;

		for ( int i = 0; i < 7; i++ )
			anim.GetCellRef(i).flame = flame;

		animator->AddAnimation(anim);
	}


	p_transform->position = hft::HFFLOAT3{ -500.f, 200.f, 5.f };
	p_transform->scale = hft::HFFLOAT3{ 150.f,150.f,1.f };


}

void TestAnimation2D::Update()
{
	SpriteAnimator* animator = GetComponent<SpriteAnimator>();

	if ( GetAsyncKeyState(VK_LEFT) & 0x8000 )
		animator->Play(TEST_ANIM_ID::WAIT);
	else
		animator->Stop(WAIT);

	if ( GetAsyncKeyState(VK_RIGHT) & 0x0001 )
		animator->Play(TEST_ANIM_ID::JUMP);

	if ( GetAsyncKeyState(VK_DOWN) & 0x8000 )
		animator->Play(TEST_ANIM_ID::RUN);
	else
		animator->Stop(RUN);
}
