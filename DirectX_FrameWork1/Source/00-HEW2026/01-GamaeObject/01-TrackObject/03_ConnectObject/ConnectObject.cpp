#include "ConnectObject.h"

#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

ConnectObject::ConnectObject()
{
	p_transform->position = hft::HFFLOAT3{ -500.f,0.f,5.f };
	p_transform->scale = hft::HFFLOAT3{ 150.f,150.f,1 };
}

void ConnectObject::Init()
{
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/AnimationTestver2.png");

	if (!tex)
	{
		return;
	}
	else
	{
		std::cout << "テストエネミーのテクスチャロード成功" << std::endl;
	}

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

	AddComponent<BoxCollider2D>();
}

void ConnectObject::Update()
{

}
