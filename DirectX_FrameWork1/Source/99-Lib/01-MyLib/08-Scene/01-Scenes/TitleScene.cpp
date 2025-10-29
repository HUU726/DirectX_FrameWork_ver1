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
		p_trf->position = hft::HFFLOAT3{ -500.f, 200.f, 5.f };
		p_trf->scale = hft::HFFLOAT3{ 150.f,150.f,1.f };
	}

	{	//球体
		sqhereObject.AddComponent<MeshRenderer>()->SetShape("sqhere");
		Transform* p_trf = sqhereObject.GetTransformPtr();
		p_trf->position = hft::HFFLOAT3{0.f,0.f,0.f};
		p_trf->scale = hft::HFFLOAT3{300.f,300.f,300.f};
	}
	{	//板
		planeObject.AddComponent<MeshRenderer>()->SetShape("plane");
		Transform* p_trf = planeObject.GetTransformPtr();
		p_trf->position = hft::HFFLOAT3{ 0.f,-400.f,0.f };
		p_trf->scale = hft::HFFLOAT3{ 400.f,0.f,400.f };
	}
	{	//立方体
		cubeObject.AddComponent<MeshRenderer>()->SetShape("cube");
		Transform* p_trf = cubeObject.GetTransformPtr();
		p_trf->position = hft::HFFLOAT3{ 700.f,0.f,0.f };
		p_trf->scale = hft::HFFLOAT3{ 400.f,40.f,400.f };
	}

	{
		Transform* p_trf = lightObject.GetTransformPtr();
		p_trf->position = { 0.f,0.f,0.f };
		p_trf->rotation = { 0,0,0 };
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
	lightObject.Update();

	{	//ライトの回転
		//Transform* p_trf = lightObject.GetTransformPtr();
		//p_trf->rotation.x += 0.01f;
		//p_trf->rotation.y += 0.01f;
		//p_trf->rotation.z += 0.01f;

		//std::cout << "Camera Rtation : " << p_trf->rotation.x << "," << p_trf->rotation.y << "," << p_trf->rotation.z << std::endl;
	}
	
	{
		float spd = 0.06f;

		Transform* p_trf = camera3D.GetTransformPtr();

		if ( GetAsyncKeyState('Q') & 0x8000 )
			p_trf->rotation.y -= 0.03f;
		if ( GetAsyncKeyState('E') & 0x8000 )
			p_trf->rotation.y += 0.03f;
	
		hft::HFFLOAT3 moveVec;
		if (GetAsyncKeyState('D') & 0x8000)
			moveVec += camera3D.GetRight();
		if (GetAsyncKeyState('A') & 0x8000)
			moveVec -= camera3D.GetRight();

		if (GetAsyncKeyState('W') & 0x8000)
			moveVec += camera3D.GetForward();
		if (GetAsyncKeyState('S') & 0x8000)
			moveVec -= camera3D.GetForward();

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			moveVec.y += 1;
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
			moveVec.y -= 1;
		
		p_trf->position += moveVec * spd;

	}
	{
		Transform* p_trf = sqhereObject.GetTransformPtr();
		//p_trf->rotation.x += 0.003f;
		//p_trf->rotation.y += 0.003f;
		//p_trf->rotation.z += 0.003f;
	}


	flameCnt++;
	if (flameCnt > 10000000000000)
		nextScene = std::make_unique<GameScene>();
}

void TitleScene::Draw()
{	
	sqhereObject.Draw();
	planeObject.Draw();
	cubeObject.Draw();
	gameObject2D.Draw();
}

void TitleScene::UnInit()
{
}
