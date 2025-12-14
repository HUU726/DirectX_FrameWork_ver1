#pragma once

#include "../../../04-Texture/Texture.h"
#include "../../../02-Renderer/01-Sprite2DRenderer/Sprite2DRenderer.h"
#include "../../00-Component/Component.h"
#include "../../../998-FH_Types/Polygon.h"


class SpriteRenderer : public Component
{
private:
	std::shared_ptr<hft::Polygon> sp_shape;		//ポリゴン(基本三角形２枚の矩形)
	hft::Polygon polygon;
	std::shared_ptr<Texture> sp_texture;		//ポリゴンにはるテクスチャー

public:
	SpriteRenderer();
	SpriteRenderer(const char* _filePath);
	SpriteRenderer(hft::Polygon& _polygon, const char* _filePath = nullptr);
	~SpriteRenderer();
	std::shared_ptr<hft::Polygon> SetShape(std::string _name);
	std::shared_ptr<hft::Polygon> SetShape(std::shared_ptr<hft::Polygon> _shape);
	std::shared_ptr<hft::Polygon> GetShape() const { return sp_shape; }
	hft::Polygon& GetPolygonRef() { return polygon; }
	std::shared_ptr<Texture> GetTexture() const { return sp_texture; }

	/**
	* @brief	画像をロード
	* @param	const char*		_filePath	ファイルパス
	* @return	std::shared_ptr<Texture>	シェアードポインタのテクスチャ
	*/
	std::shared_ptr<Texture> LoadTexture(const char* _filePath);

	void Init() override;
	void Draw() override;
	void Action() override;
};

