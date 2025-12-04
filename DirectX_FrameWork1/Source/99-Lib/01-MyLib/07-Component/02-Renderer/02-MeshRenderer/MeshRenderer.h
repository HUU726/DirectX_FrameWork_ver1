#pragma once

#include "../../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"
#include "./MeshFilter.h"
#include "../../../998-FH_Types/Mesh.h"

class MeshRenderer : public Component
{
private:
	MeshFilter* p_meshFilter;	// メッシュフィルター
	std::shared_ptr<Texture> sp_texture;
	bool isCreate = false;		// Meshを作ったかどうか


public:
	MeshRenderer();
	MeshRenderer(const char* _filePath);
	MeshRenderer(MeshFilter& _meshFilter, const char* _filePath = nullptr);
	~MeshRenderer();
	std::shared_ptr<hft::Mesh> SetShape(std::string _name);
	std::shared_ptr<hft::Mesh> SetShape(std::shared_ptr<hft::Mesh> _shape);
	std::shared_ptr<hft::Mesh> GetShape() const { return p_meshFilter->GetMesh(); }
	std::shared_ptr<Texture> GetTexture() const { return sp_texture; }

	/**
	* @brief	テクスチャをロード
	* @param	const char*		_filePath	ファイルパス
	* @return	std::shared_ptr<Texture>	シェアードポインタテクスチャ
	*/
	std::shared_ptr<Texture> LoadTexture(const char* _filePath);
	/**
	* @brief	モデルをロード
	* @param	const char*		_filePath	ファイルパス
	* @return	std::shared_ptr<hft::Mesh>	シェアードポインタメッシュ
	*/
	std::shared_ptr<hft::Mesh> LoadModel(const char* _filePath);

	void Init() override;
	void Draw() override;
	void Action() override;
};

