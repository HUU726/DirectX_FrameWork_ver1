#include "GameScene.h"
#include <iostream>
#include "../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"
#include "../../07-Component/04-Camera/02-Camera3D/Camera3D.h"

void GameScene::Init()
{
	sqhereObj.Init();
	sqhereObj.GetTransformPtr()->position = {0,0,300};

	camera3D.GetTransformPtr()->position = {200,200,-100};
	camera3D.SetTarget(&sqhereObj);
	Mesh3DRenderer::GetInstance().SetCamera(camera3D.GetComponent<Camera3D>());
}

void GameScene::UnInit()
{

}
