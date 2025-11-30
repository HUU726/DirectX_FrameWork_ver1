#include "TestPlayer.h"
#include "../../101-Time/Time.h"
#include "../../08-Scene/02-SceneManager/SceneManager.h"
#include "../../08-Scene/01-Scenes/GameScene.h"

#include <Windows.h>

void TestPlayer::Init()
{
}

void TestPlayer::Update()
{
	{
		float spd = 100.f;
		float deltaTime = Time::GetInstance().DeltaTime();

		Transform* p_trf = p_transform;

		if ( GetAsyncKeyState('Q') & 0x8000 )
			p_trf->rotation.y -= spd * deltaTime;
		if ( GetAsyncKeyState('E') & 0x8000 )
			p_trf->rotation.y += spd * deltaTime;
		if ( GetAsyncKeyState('R') & 0x8000 )
			p_trf->rotation.x -= spd * deltaTime;
		if ( GetAsyncKeyState('F') & 0x8000 )
			p_trf->rotation.x += spd * deltaTime;

		hft::HFFLOAT3 moveVec;
		if ( GetAsyncKeyState('D') & 0x8000 )
			moveVec += p_camera3D->GetRight();
		if ( GetAsyncKeyState('A') & 0x8000 )
			moveVec -= p_camera3D->GetRight();

		if ( GetAsyncKeyState('W') & 0x8000 )
			moveVec += p_camera3D->GetForward();
		if ( GetAsyncKeyState('S') & 0x8000 )
			moveVec -= p_camera3D->GetForward();

		if ( GetAsyncKeyState(VK_SPACE) & 0x8000 )
			moveVec.y += 1;
		if ( GetAsyncKeyState(VK_SHIFT) & 0x8000 )
			moveVec.y -= 1;

		p_trf->position += moveVec * spd * deltaTime;



		if ( GetAsyncKeyState(VK_UP) & 0x8000 )
			SceneManager::GetInstance().LoadScene(std::make_unique<GameScene>());

	}
}
