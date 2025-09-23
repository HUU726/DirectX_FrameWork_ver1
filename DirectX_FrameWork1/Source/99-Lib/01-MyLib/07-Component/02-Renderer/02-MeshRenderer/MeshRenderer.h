#pragma once

#include "../../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"
#include "./MeshFilter.h"

class MeshRenderer : public Component
{
private:
	MeshFilter* p_meshFilter;	// メッシュフィルター
	bool isCreate = false;		// Meshを作ったかどうか
	const char* filePath;		// 描画する画像のパス
	bool isRender = true;		// 描画処理をするかどうか

public:

	MeshRenderer();
	MeshRenderer(const char* _filePath);
	MeshRenderer(MeshFilter& _meshFilter, const char* _filePath = nullptr);
	~MeshRenderer();
	void Init() override;
	void Draw() override;
	void Draw(MeshFilter& _meshFilter);
	void Draw(Sprite2D& _sprite);
};

