#include "MeshRenderer.h"
#include "GameObject.h"

#include "Sprite2DRenderer.h"

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::MeshRenderer(const char* _filePath)
{
	if (p_meshFilter)
	{
		p_meshFilter = new	MeshFilter;
		isCreate = true;
		filePath = _filePath;
		p_meshFilter->LoadTexture(_filePath);
	}
}

MeshRenderer::MeshRenderer(MeshFilter& _meshFilter, const char* _filePath)
{
	p_meshFilter = &_meshFilter;
	if (_filePath != nullptr)
		p_meshFilter->LoadTexture(_filePath);
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
	Mesh* p_mesh = p_meshFilter->GetMesh();
	Sprite2D* p_sprite = p_meshFilter->GetSprite();

	if (p_mesh != nullptr)
	{
		p_mesh->setTransform(gameObject->GetTransform());
	}
	else if (p_sprite != nullptr)
	{
		p_sprite->setTransform(gameObject->GetTransform());
	}
}

void MeshRenderer::Draw()
{
	if (isRender)
	{
		if (p_meshFilter->GetMesh())
			Model3DRenderer::GetInstance().Draw(*p_meshFilter);
		else if (p_meshFilter->GetSprite())
			Model3DRenderer::GetInstance().Draw(*p_meshFilter->GetSprite());
	}
}

void MeshRenderer::Draw(MeshFilter& _meshFilter)
{
	if (isRender)
		Model3DRenderer::GetInstance().Draw(_meshFilter);
}

void MeshRenderer::Draw(Sprite2D& _sprite)
{
	if (isRender)
		Model3DRenderer::GetInstance().Draw(_sprite);
}
