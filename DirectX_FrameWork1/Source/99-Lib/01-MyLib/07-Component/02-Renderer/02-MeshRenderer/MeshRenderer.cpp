#include "MeshRenderer.h"
#include "../../../06-GameObject/GameObject.h"
#include "../../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"



MeshRenderer::MeshRenderer()
{
	p_meshFilter = new	MeshFilter;
	isCreate = true;
}

MeshRenderer::MeshRenderer(const char* _filePath)
{
	if (p_meshFilter)
	{
		p_meshFilter = new	MeshFilter;
		isCreate = true;
		filePath = _filePath;
		//p_meshFilter->LoadTexture(_filePath);
	}
}

MeshRenderer::MeshRenderer(MeshFilter& _meshFilter, const char* _filePath)
{
	p_meshFilter = &_meshFilter;
	//if (_filePath != nullptr)
	//	p_meshFilter->LoadTexture(_filePath);
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

void MeshRenderer::Init()
{

}

void MeshRenderer::Draw()
{
	if (isRender)
	{
		if (p_meshFilter->GetMesh())
			Mesh3DRenderer::GetInstance().Draw(p_meshFilter);

	}
}

void MeshRenderer::Draw(MeshFilter* _p_meshFilter)
{
	if (isRender)
		Mesh3DRenderer::GetInstance().Draw(_p_meshFilter);
}

void MeshRenderer::Draw(hft::Sprite2D* _p_sprite)
{
	if (isRender)
		Mesh3DRenderer::GetInstance().Draw(_p_sprite);
}
