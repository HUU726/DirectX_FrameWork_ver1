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

	{	//マップテスト
		map.Init();


	}

	//camera2D.GetComponent<Camera2D>()->SetTarget(&gameObject2D);
	//camera3D.GetComponent<Camera3D>()->SetTarget(&sqhereObject);
}


void TitleScene::UnInit()
{
}

