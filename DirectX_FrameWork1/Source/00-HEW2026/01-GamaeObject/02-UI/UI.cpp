#include "UI.h"
#include "../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../../99-Lib/01-MyLib/02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"

//シェーダーをUI用に変更
UI::UI()
{
	//画像セット
	auto renderer = GetComponent<SpriteRenderer>();
	renderer->LoadTexture("Assets/01-Texture/99-Test/Tile.jpg");

	auto animator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(0.999f, 0.999f));
	//animator->Init();
	auto div = animator->GetDivision();
	SpriteAnimation anim(div, hft::HFFLOAT2(0, 0), 1);
	anim.SetType(SPRITE_ANIM_TYPE::LOOP);
	animator->AddAnimation(anim);
	
	animator->Play(0);


	//シェーダーセット
	auto& shader = renderer->GetPolygonRef().material.shader;
	auto VS_UI2D = hft::VertexShaderTable::GetInstance().CreateShader("Source/99-Lib/01-MyLib/999-Shader/01-2D/99-UI/VS_UI2D.hlsl");

	shader.SetVertexShader(VS_UI2D);

	//サイズセット
	auto tfm = GetComponent<Transform>();

	tfm->scale = hft::HFFLOAT2{ 300.f,150.f };
	tfm->position = hft::HFFLOAT3{0.f,0.f, -10.f};

}
