#pragma once

#include "../../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"
#include "./MeshFilter.h"
#include "../../../998-FH_Types/Mesh.h"

class MeshRenderer : public Component
{
private:
	MeshFilter* p_meshFilter;	// メッシュフィルター
	Texture texture;
	bool isCreate = false;		// Meshを作ったかどうか
	const char* filePath;		// 描画する画像のパス
	bool isRender = true;		// 描画処理をするかどうか

	void SetWorldMatrix();
	void SetTexture();

public:

	MeshRenderer();
	MeshRenderer(const char* _filePath);
	MeshRenderer(MeshFilter& _meshFilter, const char* _filePath = nullptr);
	~MeshRenderer();
	std::shared_ptr<hft::Mesh> SetShape(std::string _name);
	std::shared_ptr<hft::Mesh> SetShape(std::shared_ptr<hft::Mesh> _shape);
	std::shared_ptr<hft::Mesh> GetShape() { return p_meshFilter->GetMesh(); }
	std::shared_ptr<hft::Mesh> LoadModel(const char* _filePath);
	Texture* GetTexture() { return &texture; }
	void SetBuffer();
	void Init() override;
	void Draw() override;
};

