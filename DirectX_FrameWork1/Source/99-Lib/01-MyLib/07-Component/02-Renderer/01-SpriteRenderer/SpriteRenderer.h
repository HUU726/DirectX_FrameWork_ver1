#pragma once

#include "../../../04-Texture/Texture.h"
#include "../../../02-Renderer/01-Sprite2DRenderer/Sprite2DRenderer.h"
#include "../../../998-FH_Types/Sprite2D.h"
#include "../../00-Component/Component.h"
#include "../../../02-Renderer/99-Shape/Shape.h"

using hft::Sprite2D;

class SpriteRenderer : public Component
{
private:
	std::shared_ptr<Shape> sp_shape;
	Texture texture;		// ポリゴンにはるテクスチャー
	const char* filePath;	// 描画する画像のパス
	bool isRender = true;	// 描画処理をするかどうか

public:
	SpriteRenderer();
	SpriteRenderer(const char* _filePath);
	SpriteRenderer(Shape& _shape, const char* _filePath = nullptr);
	~SpriteRenderer();
	std::shared_ptr<Shape> SetShape(std::string _name);
	std::shared_ptr<Shape> SetShape(std::shared_ptr<Shape> _shape);
	std::shared_ptr<Shape> GetShape() { return sp_shape; }
	Texture* GetTexture() { return &texture; }
	void Init() override;
	void Draw() override;
};

