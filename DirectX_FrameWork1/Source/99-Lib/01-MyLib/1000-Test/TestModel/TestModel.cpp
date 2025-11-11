#include "TestModel.h"
#include "../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"

void TestModel::Init()
{
	std::u8string modelFile = u8"Assets/02-Model/00-TestModel/cylinder.obj";
	std::string texDirectory = "Assets/02-Model/00-TestModel/";

	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	sp_staticMesh = std::make_shared<StaticMesh>();
	sp_staticMesh->Load(tmpStr1,texDirectory);

	hft::CreateVertexIndexBuffer(sp_staticMesh);

	Transform* p_trf = GetTransformPtr();
	p_trf->scale = {50,50,50};
}


void TestModel::Update()
{

}


void TestModel::Draw()
{
	Mesh3DRenderer& renderer = Mesh3DRenderer::GetInstance();
	renderer.SetVertexBuffer(sp_staticMesh->p_vertexBuffer);	//頂点バッファをセット
	renderer.SetIndexBuffer(sp_staticMesh->p_indexBuffer);
	renderer.SetWorldMatrix(GetTransform());	//ワールド行列セット

	renderer.Draw(this);
}