#include "TestObject.h"

#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"

void TestObject::Init()
{
	p_transform->scale = { 70,70,1 };
	auto renderer = GetComponent<SpriteRenderer>();
	renderer->LoadTexture("C:/Users/huuki/source/repos/DirectX_FrameWork_ver1/DirectX_FrameWork1/Assets/01-Texture/99-Test/char01.png");

	auto animator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(3, 4));
	auto div = animator->GetDivision();
	{
		SpriteAnimation anim(div, hft::HFFLOAT2(0, 0), 12);
		for (int i = 0; i < 12; i++)
		{
			anim.GetCellRef(i).flame = 15;
		}
		anim.SetType(SPRITE_ANIM_TYPE::LOOP);
		animator->AddAnimation(anim);
	}
	animator->Play(0);
}

void TestObject::Update()
{
}
