#include "MeshRenderer.h"
#include "../../../06-GameObject/GameObject.h"
#include "../../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"
#include "../../../998-FH_Types/TransformMatrix.h"
#include "../../../04-Texture/Texture.h"



MeshRenderer::MeshRenderer()
{
	p_meshFilter = new	MeshFilter;
	isCreate = true;
}

MeshRenderer::MeshRenderer(const char* _filePath)
{
	p_meshFilter = new	MeshFilter;
	isCreate = true;
}

MeshRenderer::MeshRenderer(MeshFilter& _meshFilter, const char* _filePath)
{
	p_meshFilter = &_meshFilter;
}

MeshRenderer::~MeshRenderer()
{
	if (isCreate)
	{
		delete p_meshFilter;
		p_meshFilter = nullptr;
	}
}

std::shared_ptr<hft::Mesh> MeshRenderer::SetShape(std::string _name)
{
	return p_meshFilter->SetMesh(_name);
}
std::shared_ptr<hft::Mesh> MeshRenderer::SetShape(std::shared_ptr<hft::Mesh> _shape)
{
	return p_meshFilter->SetMesh(_shape);
}

std::shared_ptr<Texture> MeshRenderer::LoadTexture(const char* _filePath)
{
	TextureTable& tTable = TextureTable::GetInstance();
	auto textureSource = tTable.LoadTexture(_filePath);

	if (textureSource)
	{
		sp_texture = textureSource;
		return sp_texture;
	}

	return nullptr;
}

std::shared_ptr<hft::Mesh> MeshRenderer::LoadModel(const char* _filePath)
{
	return p_meshFilter->LoadModel(_filePath);
}

void MeshRenderer::Init()
{

}

void MeshRenderer::Draw()
{
	if (isRender)
	{
		Mesh3DRenderer& renderer = Mesh3DRenderer::GetInstance();
		auto sp_mesh = p_meshFilter->GetMesh();
		renderer.SetVertexBuffer(sp_mesh->p_vertexBuffer);	//頂点バッファをセット
		renderer.SetIndexBuffer(sp_mesh->p_indexBuffer);	//インデックスバッファをセット
		renderer.SetTexture(sp_texture);						//テクスチャをセット

		renderer.SetWorldMatrix(gameObject->GetTransform());	//ワールド行列セット


		renderer.Draw(this);
	}
}