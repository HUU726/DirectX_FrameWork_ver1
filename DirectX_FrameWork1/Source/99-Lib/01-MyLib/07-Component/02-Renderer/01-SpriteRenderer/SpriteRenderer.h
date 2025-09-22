#pragma once

#include "../../../02-Renderer/01-Sprite2DRenderer/"
#include "Sprite2D.h"
#include "Component.h"


class SpriteRenderer : public Component
{
private:
	Sprite2D* p_sprite;		// •`‰æ‚·‚é‚à‚Ì
	bool isCreate = false;	// Sprite2D‚ğì‚Á‚½‚©‚Ç‚¤‚©
	const char* filePath;	// •`‰æ‚·‚é‰æ‘œ‚ÌƒpƒX
	bool isRender = true;	// •`‰æˆ—‚ğ‚·‚é‚©‚Ç‚¤‚©

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

