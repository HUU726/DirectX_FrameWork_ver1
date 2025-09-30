#pragma once

#include "../../../04-Texture/Texture.h"
#include "../../../02-Renderer/01-Sprite2DRenderer/Sprite2DRenderer.h"
#include "../../../998-FH_Types/Sprite2D.h"
#include "../../00-Component/Component.h"

using hft::Sprite2D;

class SpriteRenderer : public Component
{
private:
	Sprite2D* p_sprite;		// 描画するもの
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
	void Init() override;
	void Draw() override;
	void Draw(Sprite2D& _sprite);
};

