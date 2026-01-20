#include "TitleScene.h"

#include "GameScene.h"


#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"

#include "../../07-Component/04-Camera/01-Camera2D/Camera2D.h"
#include "../../07-Component/04-Camera/02-Camera3D/Camera3D.h"

#include "../../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"
#include "../../07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"

#include "../../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"

#include "../../101-Time/Time.h"





TitleScene::~TitleScene()
{

}

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

	//{	//球体
	//	sqhereObject.Init();
	//	sqhereObject.GetComponent<MeshRenderer>()->LoadTexture("Assets/01-Texture/99-Test/daruma.jpg");
	//	Transform* p_trf = sqhereObject.GetTransformPtr();
	//	p_trf->position = hft::HFFLOAT3{-300.f,200.f,0.f};
	//	p_trf->rotation = { 0,0,0 };
	//	p_trf->scale = hft::HFFLOAT3{100.f,100.f,100.f};
	//}
	//{	//板
	//	planeObject.Init();
	//	Transform* p_trf = planeObject.GetTransformPtr();
	//	p_trf->position = hft::HFFLOAT3{ 0.f,200.f,0.f };
	//	p_trf->rotation = hft::HFFLOAT3{ 0,0,0 };
	//}
	//{	//立方体
	//	cubeObject.Init();
	//	cubeObject.GetComponent<MeshRenderer>()->LoadTexture("Assets/01-Texture/99-Test/wave.png");
	//	Transform* p_trf = cubeObject.GetTransformPtr();
	//	p_trf->position = hft::HFFLOAT3{ 0.f,200.f,100.f };
	//	p_trf->scale = {100,100,100};
	//}

	//{	//地面初期化
	//	groundObject.Init();
	//	Transform* p_trf = groundObject.GetTransformPtr();
	//	p_trf->position.y = -500.f;
	//	p_trf->scale = {50,10,50};
	//}

	//{	//プレイヤーテスト
	//	testPlayer.Init();
	//	Transform* p_trf = testPlayer.GetTransformPtr();
	//	p_trf->position = { 0.f,0.f,-500.f,0.f };

	//	camera3D.SetStandPos(testPlayer.GetTransformPtr());
	//	testPlayer.SetCameraObject3D(&camera3D);
	//}

	
	//{	//アニメーション適用テスト
	//	testAnimation2D.Init();
	//	testAnimation2D.GetTransformPtr()->position = { 0,0 };
	//}
	//{	//エネミーテスト
	//	testEnemy.Init();
	//}

	{	//マップテスト
		map.Init(5, 5);
	}
	//camera2D.GetComponent<Camera2D>()->SetTarget(&gameObject2D);
	//camera3D.GetComponent<Camera3D>()->SetTarget(&sqhereObject);
	//gun.Init();
	bite.Init();
}


void TitleScene::UnInit()
{
}
