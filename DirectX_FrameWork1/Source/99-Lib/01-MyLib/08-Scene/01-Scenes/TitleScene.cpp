#include "TitleScene.h"

#include "GameScene.h"


#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"

#include "../../07-Component/04-Camera/01-Camera2D/Camera2D.h"
#include "../../07-Component/04-Camera/02-Camera3D/Camera3D.h"

void TitleScene::Init()
{
	{	//2Dカメラ初期化
		Transform* p_trf = camera2D.GetTransformPtr();
		p_trf->position = { 0.f,0.f,0.f,0.f };

		Sprite2DRenderer::GetInstance().SetCamera(camera2D.GetComponent<Camera2D>());
	}

	{	//3Dカメラ初期化
		Transform* p_trf = camera3D.GetTransformPtr();
		p_trf->position = {0.f,0.f,-500.f,0.f};

		Mesh3DRenderer::GetInstance().SetCamera(camera3D.GetComponent<Camera3D>());
	}

	{	//オブジェクト初期化
		gameObject2D.AddComponent<SpriteRenderer>()->SetShape("circle");
		Transform* p_trf = gameObject2D.GetTransformPtr();
		{
			p_trf->position = hft::HFFLOAT3{ 0.f, 0.f, 5.f };
			p_trf->scale = hft::HFFLOAT3{ 300.f,300.f,1.f };
		}
	}

	{
		gameObject3D.AddComponent<MeshRenderer>()->SetShape("cube");
		Transform* p_trf = gameObject3D.GetTransformPtr();
		{
			p_trf->position = hft::HFFLOAT3{0.f,0.f,30.f};
			p_trf->scale = hft::HFFLOAT3{300.f,300.f,300.f};
		}
	}

	//camera2D.GetComponent<Camera2D>()->SetTarget(&gameObject2D);
	//camera3D.GetComponent<Camera3D>()->SetTarget(&gameObject3D);
}

void TitleScene::Input()
{

}

void TitleScene::Update()
{
	camera2D.Update();
	camera3D.Update();
	
	{
		Transform* p_trf = camera3D.GetTransformPtr();
		p_trf->rotation.y += 0.01f;
		p_trf->rotation.x += 0.01f;
	}
	{
		Transform* p_trf = gameObject3D.GetTransformPtr();
		p_trf->rotation.y += 0.000;
	}


	flameCnt++;
	if (flameCnt > 10000000000000)
		nextScene = std::make_unique<GameScene>();
}

void TitleScene::Draw()
{	
	gameObject3D.Draw();
	//gameObject2D.Draw();
}

void TitleScene::UnInit()
{
}
