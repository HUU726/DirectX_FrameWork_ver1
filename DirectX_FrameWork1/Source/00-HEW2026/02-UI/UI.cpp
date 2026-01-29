#include "UI.h"
#include "../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../99-Lib/01-MyLib/02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"

#include "../../99-Lib/01-MyLib/03-Sound/Fsound.h"

//シェーダーをUI用に変更
UI::UI()
{	//シェーダーセット
	auto& shader = GetComponent<SpriteRenderer>()->GetPolygonRef().material.shader;
	auto VS_UI2D = hft::VertexShaderTable::GetInstance().CreateShader("Source/99-Lib/01-MyLib/999-Shader/01-2D/99-UI/VS_UI2D.hlsl");

	shader.SetVertexShader(VS_UI2D);
}

void UI::Init(const hft::HFFLOAT3 pos, const hft::HFFLOAT2 scale, const char* texName, Type_UI type)
{
	//GameObject2D側が将来共通初期化処理になった時用
	GameObject2D::Init();

	//画像セット
	auto renderer = GetComponent<SpriteRenderer>();
	renderer->LoadTexture(texName);

	//uv座標を調整
	auto animator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(0.999f, 0.999f));
	//animator->Init();
	auto div = animator->GetDivision();
	SpriteAnimation anim(div, hft::HFFLOAT2(0, 0), 1);
	anim.SetType(SPRITE_ANIM_TYPE::LOOP);
	animator->AddAnimation(anim);
	animator->Play(0);

	//UI用のシェーダーセット
	auto& shader = renderer->GetPolygonRef().material.shader;
	auto VS_UI2D = hft::VertexShaderTable::GetInstance().CreateShader("Source/99-Lib/01-MyLib/999-Shader/01-2D/99-UI/VS_UI2D.hlsl");
	shader.SetVertexShader(VS_UI2D);


	//サイズセット
	initialScale = scale;

	auto tfm = GetComponent<Transform>();
	tfm->scale = scale;
	tfm->position = pos;

	this->type = type;


	if (type == Type_UI::ButtonType)
	{
		onSE = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/10-UI/OnCursor.wav", false);
		dicSE = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/10-UI/Decision.wav", false);
	}
}

void UI::Update()
{
	//更新処理
	switch (type)
	{
	case NormalType:

		break;
	case ButtonType:

		UpdateIsMouseInside();
		UpdateIsPressed();
		UpdateIsTrigger();

		//アニメーション系の処理
		GetTransformPtr()->scale = initialScale;

		if (isPressed)
		{
			AnimationPressed();
		}
		else if (isMouseInside)
		{
			AnimationMouseInside();

			if (coverTrg)
				SoundManager::GetInstance().Play(onSE);
		}
		break;

	default:
		break;
	}
}

void UI::SetTargetKey(Button::KeyBord key)
{
	targetKey = key;
}

void UI::SetTargetXBoxButton(Button::XBox botton)
{
	targetXboxBotton = botton;
}



void UI::UpdateIsPressed()
{
	Input& input = Input::GetInstance();
	bool isMousePressed = input.GetMousePress(Button::Mouse::Left) ||
		input.GetMousePress(Button::Mouse::Right) ||
		input.GetMousePress(Button::Mouse::Middle);

	bool isKeyPressed = input.GetKeyTrigger((int)targetKey);
	bool isXBottonPressed = input.GetButtonTrigger(targetXboxBotton);

	if ((isMouseInside && isMousePressed) || isKeyPressed || isXBottonPressed)
	{
		isPressed = true;
	}
	else
	{
		isPressed = false;
	}
}

void UI::UpdateIsTrigger()
{
	isTrigger = false;

	Input& input = Input::GetInstance();
	bool isMouseTrigger = input.GetMouseTrigger(Button::Mouse::Left);
	bool isKeyTrigger = input.GetKeyTrigger((int)targetKey);
	bool isXBottonTriiger = input.GetButtonTrigger(targetXboxBotton);

	if ((isMouseInside && isMouseTrigger) || isKeyTrigger || isXBottonTriiger)
	{
		isTrigger = true;
		SoundManager::GetInstance().Play(dicSE);
	}
}

void UI::UpdateIsMouseInside()
{
	Input& input = Input::GetInstance();
	float posX = input.GetMouseCenterX();
	float posY = input.GetMouseCenterY();

	hft::HFFLOAT2 mousePos = { posX, posY };

	hft::HFFLOAT3 myPos = GetTransform().position;

	float halfW = initialScale.x * 0.5f;
	float halfH = initialScale.y * 0.5f;

	bool isInside = mousePos.x >= myPos.x - halfW &&
		mousePos.x < myPos.x + halfW &&
		mousePos.y >= myPos.y - halfH &&
		mousePos.y < myPos.y + halfH;

	preISMouseInside = isMouseInside;

	if (isInside)
	{
		isMouseInside = true;
	}
	else
	{
		isMouseInside = false;
	}

	if (isMouseInside && !preISMouseInside)
	{
		coverTrg = true;
	}
	else
	{
		coverTrg = false;
	}


}

bool UI::GetIsPressed()
{
	return isPressed;
}

bool UI::GetIsTrigger()
{
	return isTrigger;
}

bool UI::GetIsMouseInside()
{
	return isMouseInside;
}

void UI::AnimationPressed()
{
	GetTransformPtr()->scale = initialScale * 0.9f;
}

void UI::AnimationMouseInside()
{
	GetTransformPtr()->scale = initialScale * 1.1f;
}
