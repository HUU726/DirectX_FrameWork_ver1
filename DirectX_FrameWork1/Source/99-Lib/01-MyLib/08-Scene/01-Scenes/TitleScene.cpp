#include "TitleScene.h"

#include "GameScene.h"


#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/04-Camera/01-Camera2D/Camera2D.h"

void TitleScene::Init()
{
	{	//2Dカメラ初期化
		Transform* p_trf = camera2D.GetTransformPtr();
		p_trf->position = { 0.f,0.f,0.f,0.f };

		Sprite2DRenderer::GetInstance().SetCamera(camera2D.GetComponent<Camera2D>());
	
		std::cout << "Camera InitPosition：" << p_trf->position.x << "," << p_trf->position.y << "," << p_trf->position.z << std::endl;
		std::cout << "Camera InitRotation：" << p_trf->rotation.x << "," << p_trf->rotation.y << "," << p_trf->rotation.z << std::endl;
	}

	{	//3Dカメラ初期化
		Transform* p_trf = camera3D.GetTransformPtr();
		p_trf->position = {0.f,0.f,0.f,0.f};

		Mesh3DRenderer::
	}

	{	//オブジェクト初期化
		gameObject.AddComponent<SpriteRenderer>();
		Transform* p_trf = gameObject.GetTransformPtr();
		{
			p_trf->position = hft::HFFLOAT4{ 0.f, 0.f, 5.f, 0.f };
			p_trf->scale = hft::HFFLOAT3{ 300.f,300.f,1.f };

			std::cout << "Object InitPosition：" << p_trf->position.x << "," << p_trf->position.y << "," << p_trf->position.z << std::endl;
		}
	}

	//camera2D.GetComponent<Camera2D>()->SetTarget(&gameObject);
}

void TitleScene::Input()
{

}

void TitleScene::Update()
{
	camera2D.Update();
	//camera2D.GetTransformPtr()->position.x -= 0.002f;
	gameObject.GetTransformPtr()->rotation.z += 0.005f;
	gameObject.GetTransformPtr()->position.x += 0.005f;

	flameCnt++;
	if (flameCnt > 10000000000000)
		nextScene = std::make_unique<GameScene>();
}

void TitleScene::Draw()
{	
	gameObject.Draw();
}

void TitleScene::UnInit()
{
}
