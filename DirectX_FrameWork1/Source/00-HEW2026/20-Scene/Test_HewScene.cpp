#include "Test_HewScene.h"

#include "../../99-Lib/01-MyLib/02-Renderer/01-Sprite2DRenderer/Sprite2DRenderer.h"
#include "../../99-Lib/01-MyLib/02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"

#include "../../99-Lib/01-MyLib/07-Component/04-Camera/01-Camera2D/Camera2D.h"
#include "../../99-Lib/01-MyLib/07-Component/04-Camera/02-Camera3D/Camera3D.h"


void Test_HewScene::Init()
{
	{	//2DƒJƒƒ‰‰Šú‰»
		Transform* p_trf = camera2D.GetTransformPtr();
		p_trf->position = { 0.f,0.f,0.f,0.f };

		Sprite2DRenderer::GetInstance().SetCamera(camera2D.GetComponent<Camera2D>());
	}

	{	//3DƒJƒƒ‰‰Šú‰»
		Transform* p_trf = camera3D.GetTransformPtr();
		p_trf->position = { 0.f,0.f,-500.f,0.f };

		Mesh3DRenderer::GetInstance().SetCamera(camera3D.GetComponent<Camera3D>());
	}

	obj.Init();
}

void Test_HewScene::UnInit()
{
}
