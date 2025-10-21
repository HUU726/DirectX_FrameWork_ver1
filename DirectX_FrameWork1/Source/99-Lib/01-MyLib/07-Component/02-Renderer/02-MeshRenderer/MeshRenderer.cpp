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

void MeshRenderer::Init()
{
	hft::Mesh* p_mesh = p_meshFilter->GetMesh();
	hft::Sprite2D* p_sprite = p_meshFilter->GetSprite();

	if (p_mesh != nullptr)
	{
		p_mesh->p_transform =  gameObject->GetTransformPtr();
	}
	else if (p_sprite != nullptr)
	{
		p_sprite->p_transform = gameObject->GetTransformPtr();;
	}
}

void MeshRenderer::Draw()
{
	if (isRender)
	{
		if (p_meshFilter->GetMesh())
			Mesh3DRenderer::GetInstance().Draw(p_meshFilter);
		else if (p_meshFilter->GetSprite())
			Mesh3DRenderer::GetInstance().Draw(p_meshFilter->GetSprite());
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
