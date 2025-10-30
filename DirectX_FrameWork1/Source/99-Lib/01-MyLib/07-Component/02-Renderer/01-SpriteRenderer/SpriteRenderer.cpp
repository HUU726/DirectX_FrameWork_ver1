#include "SpriteRenderer.h"
#include "../../../06-GameObject/GameObject.h"
#include "../../../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"

SpriteRenderer::SpriteRenderer()
{
	sp_shape = ShapeTable2D::GetInstance().GetShape("sprite");
}

SpriteRenderer::SpriteRenderer(const char* _filePath)
{
}

SpriteRenderer::SpriteRenderer(hft::Polygon& _shape, const char* _filePath)
{
	sp_shape = ShapeTable2D::GetInstance().GetShape(_shape.name);
}

SpriteRenderer::~SpriteRenderer()
{
}

std::shared_ptr<hft::Polygon> SpriteRenderer::SetShape(std::string _name)
{
	sp_shape = ShapeTable2D::GetInstance().GetShape(_name);
	return std::shared_ptr<hft::Polygon>();
}

std::shared_ptr<hft::Polygon> SpriteRenderer::SetShape(std::shared_ptr<hft::Polygon> _shape)
{
	sp_shape = ShapeTable2D::GetInstance().GetShape(_shape->name);
    return sp_shape;
}

void SpriteRenderer::Init()
{
}

void SpriteRenderer::Draw()
{
	if (isRender)
	{
		Sprite2DRenderer& renderer = Sprite2DRenderer::GetInstance();
		
		renderer.SetVertexBuffer(sp_shape->p_vertexBuffer);
		renderer.SetIndexBuffer(sp_shape->p_indexBuffer);
		renderer.SetTexture(sp_texture);

		renderer.SetWorldMatrix(gameObject->GetTransform());
		renderer.SetVPMatrix();

		renderer.Draw(this);
	}
}


