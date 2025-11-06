#include "TitleScene.h"

#include "GameScene.h"


#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"

#include "../../07-Component/04-Camera/01-Camera2D/Camera2D.h"
#include "../../07-Component/04-Camera/02-Camera3D/Camera3D.h"

#include "../../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"
#include "../../07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"

#include "../../101-Time/Time.h"

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
		{
			gameObject2D.AddComponent<SpriteRenderer>();
			gameObject2D.GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/AnimationTest.png");
			SpriteAnimator* animator = gameObject2D.AddComponent<SpriteAnimator>(hft::HFFLOAT2(4,4));
			hft::HFFLOAT2 div = animator->GetDivision();
			{
				SpriteAnimation anim(div, { 0,0 }, 5);
				anim.SetID(0);
				anim.SetType(SPRITE_ANIM_TYPE::BOOMERANG);
				anim.SetPriority(0);
				float flame = 20;

				for (int i = 0; i < 5; i++)
					anim.GetCell(i).flame = flame;

				animator->AddAnimation(anim);
			}
			{
				SpriteAnimation anim(div, { 1,1 }, 4);
				anim.SetID(1);
				anim.SetType(SPRITE_ANIM_TYPE::LOOP);
				anim.SetPriority(1);
				float flame(40);
				for (int i = 0; i < 4; i++)
					anim.GetCell(i).flame = flame;

				animator->AddAnimation(anim);
			}

		}

		Transform* p_trf = gameObject2D.GetTransformPtr();
		p_trf->position = hft::HFFLOAT3{ -500.f, 200.f, 5.f };
		p_trf->scale = hft::HFFLOAT3{ 150.f,150.f,1.f };
	}

	{	//球体
		sqhereObject.AddComponent<MeshRenderer>()->SetShape("sqhere");
		sqhereObject.GetComponent<MeshRenderer>()->LoadTexture("Assets/01-Texture/99-Test/daruma.jpg");
		Transform* p_trf = sqhereObject.GetTransformPtr();
		p_trf->position = hft::HFFLOAT3{0.f,0.f,0.f};
		p_trf->rotation = { 0,0,0 };
		p_trf->scale = hft::HFFLOAT3{300.f,300.f,300.f};
	}
	{	//板
		planeObject.AddComponent<MeshRenderer>()->SetShape("plane");
		Transform* p_trf = planeObject.GetTransformPtr();
		p_trf->position = hft::HFFLOAT3{ 0.f,-400.f,0.f };
		p_trf->rotation = hft::HFFLOAT3{ 0,0,0 };
		p_trf->scale = hft::HFFLOAT3{ 600.f,1.f,600.f };
	}
	{	//立方体
		cubeObject.AddComponent<MeshRenderer>()->SetShape("cube");
		cubeObject.GetComponent<MeshRenderer>()->LoadTexture("Assets/01-Texture/99-Test/wave.png");
		Transform* p_trf = cubeObject.GetTransformPtr();
		p_trf->position = hft::HFFLOAT3{ 700.f,0.f,0.f };
		p_trf->rotation = hft::HFFLOAT3{ 20,0,45 };
		p_trf->scale = hft::HFFLOAT3{ 400.f,400.f,400.f };
	}

	//camera2D.GetComponent<Camera2D>()->SetTarget(&gameObject2D);
	camera3D.GetComponent<Camera3D>()->SetTarget(&sqhereObject);
}

void TitleScene::Input()
{

}

void TitleScene::Update()
{
	camera2D.Update();
	camera3D.Update();
	lightObject.Update();
	SpriteAnimator* animator = gameObject2D.GetComponent<SpriteAnimator>();
	
	animator->Stop(0);
	animator->Stop(1);

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		animator->Play(0);
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		animator->Play(1);

	animator->Update();

	{
		float spd = 100.f;
		float deltaTime = Time::GetInstance().DeltaTime();

		Transform* p_trf = camera3D.GetTransformPtr();

		if (GetAsyncKeyState('Q') & 0x8000)
			p_trf->rotation.y -= spd * deltaTime;
		if ( GetAsyncKeyState('E') & 0x8000 )
			p_trf->rotation.y += spd * deltaTime;
		if ( GetAsyncKeyState('R') & 0x8000 )
			p_trf->rotation.x -= spd * deltaTime;
		if ( GetAsyncKeyState('F') & 0x8000 )
			p_trf->rotation.x += spd * deltaTime;
	
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
		
		p_trf->position += moveVec * spd * deltaTime;

	}
	{	//デバッグ用
		bool isDraw = false;
		if (GetAsyncKeyState('M') & 0x0001)
			isDraw = true;

		if (isDraw)
		{
			Transform* p_cameraTrf = camera3D.GetTransformPtr();
			Transform* p_lightTrf = lightObject.GetTransformPtr();
			Transform* p_sqhereTrf = sqhereObject.GetTransformPtr();

			std::cout << "Camera3D Position : " << p_cameraTrf->position.x << "," << p_cameraTrf->position.y << "," << p_cameraTrf->position.z << std::endl;
			std::cout << "light    Position : " << p_lightTrf->position.x << "," << p_lightTrf->position.y << "," << p_lightTrf->position.z << std::endl;
			std::cout << "sqhere   Position : " << p_sqhereTrf->position.x << "," << p_sqhereTrf->position.y << "," << p_sqhereTrf->position.z << std::endl << std::endl;

			std::cout << "light    Rotation : " << p_lightTrf->rotation.x << "," << p_lightTrf->rotation.y << "," << p_lightTrf->rotation.z << std::endl;
			std::cout << "sqhere   Rotation : " << p_sqhereTrf->rotation.x << "," << p_sqhereTrf->rotation.y << "," << p_sqhereTrf->rotation.z << std::endl;
			std::cout << std::endl << std::endl << std::endl;
		}
	}

	{
		Transform* p_trf = sqhereObject.GetTransformPtr();
		p_trf->rotation.x += 0.003f;
		p_trf->rotation.y += 0.003f;
		p_trf->rotation.z += 0.003f;
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
	lightObject.Draw();
	gameObject2D.Draw();
}

void TitleScene::UnInit()
{
}
