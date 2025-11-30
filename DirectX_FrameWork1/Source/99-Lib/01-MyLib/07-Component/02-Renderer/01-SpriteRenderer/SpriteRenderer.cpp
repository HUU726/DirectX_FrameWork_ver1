#include "SpriteRenderer.h"
#include "../../../06-GameObject/GameObject.h"
#include "../../../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"
#include "../../06-Animator/01-SpriteAnimator/SpriteAnimator.h"

#include "../../99-CompMng/ComponentManager.h"


SpriteRenderer::SpriteRenderer()
{
	ComponentManager<SpriteRenderer>::GetInstance().Add(this);

	sp_shape = ShapeTable2D::GetInstance().GetShape("sprite");
}

SpriteRenderer::SpriteRenderer(const char* _filePath)
{
	ComponentManager<SpriteRenderer>::GetInstance().Add(this);
}

SpriteRenderer::SpriteRenderer(hft::Polygon& _shape, const char* _filePath)
{
	ComponentManager<SpriteRenderer>::GetInstance().Add(this);
	sp_shape = ShapeTable2D::GetInstance().GetShape(_shape.name);
}

SpriteRenderer::~SpriteRenderer()
{
	ComponentManager<SpriteRenderer>::GetInstance().Remove(this);
}

std::shared_ptr<hft::Polygon> SpriteRenderer::SetShape(std::string _name)
{
	sp_shape = ShapeTable2D::GetInstance().GetShape(_name);
	return std::shared_ptr<hft::Polygon>();
}

std::shared_ptr<hft::Polygon> SpriteRenderer::SetShape(std::shared_ptr<hft::Polygon> _shape)
{
	sp_shape = _shape;
    return sp_shape;
}

std::shared_ptr<Texture> SpriteRenderer::LoadTexture(const char* _filePath)
{
	TextureTable& tTable = TextureTable::GetInstance();
	auto textureSource = tTable.LoadTexture(_filePath);

	if (textureSource)
	{
		sp_texture = textureSource;
		this->sp_shape->material.isTexture = 1;
		return sp_texture;
	}

	return nullptr;
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

		
		if (const auto& comp = gameObject->GetComponent<SpriteAnimator>())
		{
			comp->SendTex();
		}
		else
		{
			renderer.SetTex();
		}

		renderer.SetWorldMatrix(gameObject->GetTransform());
		renderer.SetVPMatrix();

		renderer.Draw(this);
	}
}

void SpriteRenderer::Action()
{
	Draw();
}


