#include "System.h"

#include "../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"
#include "../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../999-Shader/99-ShaderTable/ShaderTable.h"
#include "../07-Component/99-CompMng/ComponentManager.h"

System::System()
{
	ShapeTable2D::GetInstance();
	ShapeTable3D::GetInstance();
	hft::PixelShaderTable::GetInstance();
	hft::VertexShaderTable::GetInstance();

	compMngs.resize(COMP_MNG_TYPES::COMP_MAX);
}

void System::AddCompMng(IF_ComponentManager* _p_compMng)
{
	auto it = std::find(compMngs.begin(), compMngs.end(), _p_compMng);
	if ( it == compMngs.end())
	{
		compMngs[_p_compMng->GetType()] = _p_compMng;
	}
}

void System::InitSystem(HWND _hwnd)
{
	rendererMng.Init(_hwnd);
}
void System::UnInitSystem()
{
	rendererMng.UnInit();
	compMngs.clear();
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
	gameObjMng.Clear();
}



void System::InputCompMngAction()
{
	compMngs[COMP_MNG_TYPES::COMP_INPUT]->Action();
}

void System::GameObjectMngAction()
{
	gameObjMng.Action();
}

void System::BeforeRender_CompMngsAction()
{
	int compMngIndex = COMP_MNG_TYPES::COMP_INPUT + 1;
	for (; compMngIndex < COMP_MNG_TYPES::COMP_BEFORE_RENDER; compMngIndex++)
	{
		compMngs[compMngIndex]->Action();
	}
}

void System::RendererCompMngAction()
{
	rendererMng.ClearScreen();
	compMngs[COMP_MNG_TYPES::COMP_RENDERER3D]->Action();
	compMngs[COMP_MNG_TYPES::COMP_RENDERER2D]->Action();
	rendererMng.SwapChain();
}
