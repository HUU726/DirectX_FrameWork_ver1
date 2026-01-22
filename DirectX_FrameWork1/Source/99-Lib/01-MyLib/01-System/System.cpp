#include "System.h"

#include "../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"
#include "../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../999-Shader/99-ShaderTable/ShaderTable.h"
#include "../07-Component/99-CompMng/ComponentManager.h"
#include "../08-Scene/02-SceneManager/SceneManager.h"

#include "../../../04-Input/Input.h"	//朝日奈担当の入力系クラス
#include "../03-Sound/Fsound.h"

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
	rendererMng.Init(_hwnd);	//レンダラーマネージャーを初期化

	ShapeTable2D::GetInstance().Init();	//2Dの形状保存テーブルを初期化
	ShapeTable3D::GetInstance().Init();	//3Dの形状保存てーむるを初期化
	hft::PixelShaderTable::GetInstance().Init();	//ピクセルシェーダテーブルを初期化
	hft::VertexShaderTable::GetInstance().Init();	//バーテックスシェーダーテーブルを初期化

	SoundManager::GetInstance().Init();	//サウンドマネージャーを初期化
	SceneManager::GetInstance().Init();	//シーンマネージャーを初期化

}
void System::UnInit()
{
	{
		rendererMng.UnInit();
		std::vector<IF_ComponentManager*> swapCompMngs;
		swapCompMngs.swap(compMngs);
		gameObjMng.Clear();
	}

	ShapeTable2D::GetInstance().ClearTable();
	ShapeTable3D::GetInstance().ClearTable();
	hft::PixelShaderTable::GetInstance().ClearTable();
	hft::VertexShaderTable::GetInstance().ClearTable();
	SceneManager::GetInstance().UnInit();
	SoundManager::GetInstance().Uninit();
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
	if (compMngs[COMP_MNG_TYPES::COMP_INPUT] != nullptr )
		compMngs[COMP_MNG_TYPES::COMP_INPUT]->Action();
}

void System::GameObjectMngAction()
{
	gameObjMng.Action();
}

/**
* @brief	InputコンポネントとRendererコンポネントの間のコンポネントを更新
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
* @brief	描画系コンポネントの処理実行
* @note		3D → 2D	の順番で描画
*/
void System::RendererCompMngAction()
{
	rendererMng.ClearScreen();
	if (compMngs[COMP_MNG_TYPES::COMP_RENDERER3D] != nullptr)
		compMngs[COMP_MNG_TYPES::COMP_RENDERER3D]->Action();
	if (compMngs[COMP_MNG_TYPES::COMP_RENDERER2D] != nullptr)
		compMngs[COMP_MNG_TYPES::COMP_RENDERER2D]->Action();
	rendererMng.SwapChain();
}
