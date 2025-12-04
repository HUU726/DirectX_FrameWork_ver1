#include "TestEnemy.h"

#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

TestEnemy::TestEnemy()
{
	p_transform->position = hft::HFFLOAT3{ -500.f,0.f,5.f };
	p_transform->scale = hft::HFFLOAT3{ 150.f,150.f,1 };
}

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
			anim.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim);
	}

	AddComponent<BoxCollider2D>();
}

void TestEnemy::Update()
{
	if ( GetAsyncKeyState('M') & 0x8000 )
		p_spriteAnimator->Play(0);
	else
		p_spriteAnimator->Stop(0);


	hft::HFFLOAT3 moveVec;
	float speed = 1.f;
	if (GetAsyncKeyState('W') & 0x8000)
		moveVec.y += 1;

	p_transform->position += moveVec * speed;
}
