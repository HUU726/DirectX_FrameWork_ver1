#include "SpriteRenderer.h"
#include "../../../06-GameObject/GameObject.h"
#include "../../../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"
#include "../../06-Animator/01-SpriteAnimator/SpriteAnimator.h"

#include "../../99-CompMng/ComponentManager.h"


SpriteRenderer::SpriteRenderer()
{
	ComponentManager<SpriteRenderer>::GetInstance().Add(this);

	sp_shape = ShapeTable2D::GetInstance().GetShape("sprite");
	polygon = *sp_shape;
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
	polygon = *ShapeTable2D::GetInstance().GetShape(_name);
	return std::shared_ptr<hft::Polygon>();
}

std::shared_ptr<hft::Polygon> SpriteRenderer::SetShape(std::shared_ptr<hft::Polygon> _shape)
{
	sp_shape = _shape;
	polygon = *_shape;
    return sp_shape;
}

/**
* @brief	TextureTableに問いかけてその画像が存在すればそのポインタを
*			存在しなければロードする
*/
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
	if (isActive)
	{
		Sprite2DRenderer& renderer = Sprite2DRenderer::GetInstance();
		
		renderer.SetVertexBuffer(sp_shape->p_vertexBuffer);
		renderer.SetIndexBuffer(sp_shape->p_indexBuffer);

		//renderer.SetVertexBuffer(polygon.p_vertexBuffer);
		//renderer.SetIndexBuffer(polygon.p_indexBuffer);
		renderer.SetTexture(sp_texture);
		renderer.SetMaterial(polygon.material);

		if (const auto& animator = gameObject->GetComponent<SpriteAnimator>())
		{
			//所属GameObjectにSpriteAnimatorコンポネントが存在すればそのUV座標を送る
			animator->SendTex();
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


