#include "BaseScene.h"

#include "../../../06-GameObject/999-GameObjectManager/GameObjectManager.h"

#include "../../../02-Renderer/01-Sprite2DRenderer/Sprite2DRenderer.h"
#include "../../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"
#include "../../../07-Component/04-Camera/01-Camera2D/Camera2D.h"
#include "../../../07-Component/04-Camera/02-Camera3D/Camera3D.h"

void BaseScene::InitCamera()
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
}

BaseScene::BaseScene()
{
	InitCamera();
}
