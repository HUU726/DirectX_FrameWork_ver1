#pragma once

#include "../../../04-Texture/Texture.h"
#include "../../../02-Renderer/01-Sprite2DRenderer/Sprite2DRenderer.h"
#include "../../../998-FH_Types/Sprite2D.h"
#include "../../00-Component/Component.h"
#include "../../../998-FH_Types/Polygon.h"

using hft::Sprite2D;

class SpriteRenderer : public Component
{
private:
	std::shared_ptr<hft::Polygon> sp_shape;
	std::shared_ptr<Texture> sp_texture;		// ポリゴンにはるテクスチャー
	bool isRender = true;	// 描画処理をするかどうか

public:
	SpriteRenderer();
	SpriteRenderer(const char* _filePath);
	SpriteRenderer(hft::Polygon& _polygon, const char* _filePath = nullptr);
	~SpriteRenderer();
	std::shared_ptr<hft::Polygon> SetShape(std::string _name);
	std::shared_ptr<hft::Polygon> SetShape(std::shared_ptr<hft::Polygon> _shape);
	std::shared_ptr<hft::Polygon> GetShape() { return sp_shape; }
	std::shared_ptr<Texture> GetTexture() { return sp_texture; }
	void Init() override;
	void Draw() override;
};

