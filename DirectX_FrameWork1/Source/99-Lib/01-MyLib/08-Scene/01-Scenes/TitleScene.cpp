#include "TitleScene.h"

#include "GameScene.h"


#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/04-Camera/01-Camera2D/Camera2D.h"

void TitleScene::Init()
{
	{	//カメラ初期化
		Transform* p_trf = camera2D.GetTransformPtr();
		p_trf->position = { 0.f,0.f,-1.f };

		Sprite2DRenderer::GetInstance().SetCamera(camera2D.GetComponent<Camera2D>());
	}

	{	//オブジェクト初期化
		gameObject.AddComponent<SpriteRenderer>();
		Transform* p_trf = gameObject.GetTransformPtr();
		{
			p_trf->position = hft::HFFLOAT4{ 0.f, 0.f, 5.f, 0.f };
			p_trf->scale = hft::HFFLOAT3{ 300.f,300.f,1.f };
		}
	}
}

void TitleScene::Input()
{

}

void TitleScene::Update()
{
	camera2D.Update();

	flameCnt++;
	if (flameCnt > 1000)
		nextScene = std::make_unique<GameScene>();
}

void TitleScene::Draw()
{	
	gameObject.Draw();
}

void TitleScene::UnInit()
{
}
