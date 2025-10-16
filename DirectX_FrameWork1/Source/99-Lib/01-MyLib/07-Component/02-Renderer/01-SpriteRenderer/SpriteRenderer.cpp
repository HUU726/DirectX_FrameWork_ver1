#include "SpriteRenderer.h"
#include "../../../06-GameObject/GameObject.h"
#include "../../../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"

SpriteRenderer::SpriteRenderer()
{}

SpriteRenderer::SpriteRenderer(const char* _filePath)
{
		filePath = _filePath;
		texture.LoadTexture(_filePath);
}

SpriteRenderer::SpriteRenderer(Shape2D& _shape, const char* _filePath)
{
	sp_shape = ShapeTable2D::GetInstance().GetShape(_shape.name);

	if (_filePath)
		texture.LoadTexture(_filePath);
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Init()
{
}

void SpriteRenderer::Draw()
{
	if (isRender)
	{
		Sprite2DRenderer::GetInstance().Draw(this);
	}
}


