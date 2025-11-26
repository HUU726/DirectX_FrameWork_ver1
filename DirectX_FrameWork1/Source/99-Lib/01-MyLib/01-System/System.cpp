#include "System.h"

#include "../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"
#include "../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../999-Shader/99-ShaderTable/ShaderTable.h"
#include "../07-Component/99-CompMng/CompornentManager.h"


System::System()
{
	ShapeTable2D::GetInstance();
	ShapeTable3D::GetInstance();
	hft::PixelShaderTable::GetInstance();
	hft::VertexShaderTable::GetInstance();

	compMngers.resize(COMP_MNG_TYPES::MAX_COMP);
}

void System::AddCompMng(Base_ComponentManager* _p_compMng)
{
	auto it = std::find(compMngers.begin(), compMngers.end(), _p_compMng);
	if ( it == compMngers.end())
	{
		compMngers[_p_compMng->GetType()] = _p_compMng;
	}
}

void System::Init()
{
	
}

void System::ActionComponentMng()
{
}

void System::UnInit()
{
	compMngers.clear();
}
