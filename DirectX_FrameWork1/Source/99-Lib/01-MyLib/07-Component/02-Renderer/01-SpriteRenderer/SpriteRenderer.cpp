#include "SpriteRenderer.h"
#include "../../../06-GameObject/GameObject.h"

SpriteRenderer::SpriteRenderer()
{
	p_sprite = new Sprite2D;
	isCreate = true;
}

SpriteRenderer::SpriteRenderer(const char* _filePath)
{
		p_sprite = new Sprite2D;
		isCreate = true;
		filePath = _filePath;
		texture.LoadTexture(_filePath);
}

SpriteRenderer::SpriteRenderer(Sprite2D& _sprite, const char* _filePath)
{
	p_sprite = &_sprite;

	if (_filePath != nullptr)
		texture.LoadTexture(_filePath);
}

SpriteRenderer::~SpriteRenderer()
{
	if (isCreate)
	{
		delete p_sprite;
		p_sprite = nullptr;
	}
}

void SpriteRenderer::Init()
{
	p_sprite->p_transform = gameObject->GetTransformPtr();
}

void SpriteRenderer::Draw()
{
	if (isRender)
		Sprite2DRenderer::GetInstance().Draw(p_sprite);
}

void SpriteRenderer::Draw(Sprite2D& _sprite)
{
	if (isRender)
	{
		Sprite2DRenderer::GetInstance().Draw(&_sprite);
	}
}

void SpriteRenderer::Draw(SpriteRenderer* _renderer)
{
	if (isRender)
	{
		Sprite2DRenderer::GetInstance().Draw(this);
	}
}


