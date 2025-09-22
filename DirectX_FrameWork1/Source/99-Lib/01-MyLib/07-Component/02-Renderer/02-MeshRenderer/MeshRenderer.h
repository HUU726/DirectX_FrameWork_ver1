#pragma once

#include "Model3DRenderer.h"
#include "Mesh.h"
#include "Component.h"

class MeshRenderer : public Component
{
private:
	MeshFilter* p_meshFilter;	// メッシュフィルター
	bool isCreate = false;		// Meshを作ったかどうか
	const char* filePath;		// 描画する画像のパス
	bool isRender = true;		// 描画処理をするかどうか


	GEN_COMPONENT_ID(MeshRenderer)

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

