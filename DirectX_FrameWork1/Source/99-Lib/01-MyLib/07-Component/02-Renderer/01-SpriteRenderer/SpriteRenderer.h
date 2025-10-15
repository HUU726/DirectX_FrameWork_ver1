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
	Sprite2D* p_sprite;		// 描画するもの
	std::shared_ptr<Shape2D> sp_shape;
	Texture texture;		// ポリゴンにはるテクスチャー
	bool isCreate = false;	// Sprite2Dを作ったかどうか
	const char* filePath;	// 描画する画像のパス
	bool isRender = true;	// 描画処理をするかどうか

public:
	SpriteRenderer();
	SpriteRenderer(const char* _filePath);
	SpriteRenderer(Sprite2D& _sprite, const char* _filePath = nullptr);
	~SpriteRenderer();
	void SetSprite(Sprite2D& _sprite)
	{ 
		*p_sprite = _sprite;
	}
	Sprite2D* GetSprite() { return p_sprite; }
	std::shared_ptr<Shape2D> GetShape() { return sp_shape; }
	Texture* GetTexture() { return &texture; }
	void Init() override;
	void Draw() override;
	void Draw(Sprite2D& _sprite);
	void Draw(SpriteRenderer* _renderer);
};

