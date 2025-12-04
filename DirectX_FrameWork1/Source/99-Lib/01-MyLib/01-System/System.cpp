#include "System.h"

#include "../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"
#include "../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../999-Shader/99-ShaderTable/ShaderTable.h"
#include "../07-Component/99-CompMng/ComponentManager.h"
#include "../08-Scene/02-SceneManager/SceneManager.h"

System::System()
{
	int size = COMP_MNG_TYPES::COMP_MAX;
	compMngs.resize(size);
}

void System::AddCompMng(IF_ComponentManager* _p_compMng)
{
	auto it = std::find(compMngs.begin(), compMngs.end(), _p_compMng);
	if ( it == compMngs.end())
	{
		int typeIndex = _p_compMng->GetType();
		compMngs[typeIndex] = _p_compMng;
	}
}

void System::Init(HWND _hwnd)
{
	rendererMng.Init(_hwnd);

	ShapeTable2D::GetInstance();
	ShapeTable3D::GetInstance();
	hft::PixelShaderTable::GetInstance();
	hft::VertexShaderTable::GetInstance();

	SceneManager& sceneMng = SceneManager::GetInstance();
	sceneMng.Init();
}
void System::UnInit()
{
	rendererMng.UnInit();
	compMngs.clear();
	gameObjMng.Clear();
}

void System::GameLoopPipeline()
{
	InputCompMngAction();
	GameObjectMngAction();
	BeforeRender_CompMngsAction();
	RendererCompMngAction();
}

void System::ClearManagersData()
{
}



void System::InputCompMngAction()
{
	if (compMngs[COMP_MNG_TYPES::COMP_INPUT] != nullptr )
		compMngs[COMP_MNG_TYPES::COMP_INPUT]->Action();
}

void System::GameObjectMngAction()
{
	gameObjMng.Action();
}

/**
* @brief	
*/
void System::BeforeRender_CompMngsAction()
{
	int compMngIndex = COMP_MNG_TYPES::COMP_INPUT + 1;
	for (; compMngIndex < COMP_MNG_TYPES::COMP_BEFORE_RENDER; compMngIndex++)
	{
		if (compMngs[compMngIndex] != nullptr )
			compMngs[compMngIndex]->Action();
	}
}

/**
* @brief	•`‰æŒnƒRƒ“ƒ|ƒlƒ“ƒg‚Ìˆ—ŽÀs
* @note		3D ¨ 2D	‚Ì‡”Ô‚Å•`‰æ
*/
void System::RendererCompMngAction()
{
	rendererMng.ClearScreen();
	compMngs[COMP_MNG_TYPES::COMP_RENDERER3D]->Action();
	compMngs[COMP_MNG_TYPES::COMP_RENDERER2D]->Action();
	rendererMng.SwapChain();
}
