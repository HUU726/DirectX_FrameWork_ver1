#include "01_Hew_TitleScene.h"

#include "../../02-App/Application.h"
#include "../../02-App/HF_Window.h"

void Hew_TitleScene::Init()
{
	{	//îwåi
		BGImg.GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/20-BGImg/01-Title/title1.png");

		auto p_window = Application::GetInstance().GetWindowPtr();
		float width = p_window->GetWidth();
		float height = p_window->GetHeight();

		BGImg.GetTransformPtr()->position.z = 1;
		BGImg.GetTransformPtr()->scale = { width,height,1 };
	}
}

void Hew_TitleScene::UnInit()
{
}
