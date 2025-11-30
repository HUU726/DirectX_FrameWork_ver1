#include "TestEnemy.h"

#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

void TestEnemy::Init()
{
	GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/AnimationTestver2.png");
	p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(3,3));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	{
		SpriteAnimation anim(div, {0,0}, 9);
		anim.SetID(0);
		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim.SetPriority(0);
		float flame = 60;

		for ( int i = 0; i < 9; i++ )
		{
			anim.GetCell(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim);
	}

	p_transform->position = hft::HFFLOAT3{ 0.f,0.f,5.f };
	p_transform->scale = hft::HFFLOAT3{150.f,150.f,1};
}

void TestEnemy::Update()
{
	if ( GetAsyncKeyState('M') & 0x8000 )
		p_spriteAnimator->Play(0);
	else
		p_spriteAnimator->Stop(0);
}
