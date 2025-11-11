#include "StaticMesh.h"
#include "../AssimpParse/AssimpPerse.h"

void StaticMesh::Load(std::string _filePath, std::string _textureDirectory)
{
	std::vector<AssimpPerse::SUBSET> l_subsets{};					// サブセット情報
	std::vector<std::vector<AssimpPerse::VERTEX>> l_vertices{};	// 頂点データ（メッシュ単位）
	std::vector<std::vector<unsigned int>> l_indices{};			// インデックスデータ（メッシュ単位）
	std::vector<AssimpPerse::MATERIAL> l_materials{};				// マテリアル
	std::vector<std::unique_ptr<Texture>> l_embededTextures{};	// 内蔵テクスチャ群

	// assimpを使用してモデルデータを取得
	AssimpPerse::GetModelData(_filePath, _textureDirectory);

	l_subsets = AssimpPerse::GetSubsets();		// サブセット情報取得
	l_vertices = AssimpPerse::GetVertices();	// 頂点データ（メッシュ単位）
	l_indices = AssimpPerse::GetIndices();		// インデックスデータ（メッシュ単位）
	l_materials = AssimpPerse::GetMaterials();	// マテリアル情報取得

	textures = AssimpPerse::GetTextures();	// テクスチャ情報取得

	// 頂点データ作成
	for ( const auto& mv : l_vertices )
	{
		for ( auto& v : mv )
		{
			hft::Vertex vertex{};
			vertex.position = hft::HFFLOAT3(v.pos.x, v.pos.y, v.pos.z);
			vertex.normal = hft::HFFLOAT3(v.normal.x, v.normal.y, v.normal.z);
			vertex.uv = hft::HFFLOAT2(v.texcoord.x, v.texcoord.y);
			vertex.color = hft::HFFLOAT4(v.color.r, v.color.g, v.color.b, v.color.a);

			vertices.emplace_back(vertex);
		}
	}

	// インデックスデータ作成
	for ( const auto& mi : l_indices )
	{
		for ( auto& index : mi )
		{
			indices.emplace_back(index);
		}
	}

	// サブセットデータ作成
	for ( const auto& sub : l_subsets )
	{
		hft::Subset subset{};
		subset.vertexBase = sub.VertexBase; // 頂点の開始位置
		subset.vertexNum = sub.VertexNum; // サブセット内の頂点数
		subset.indexBase = sub.IndexBase;  // インデックスの開始位置
		subset.indexNum = sub.IndexNum; // サブセット内のインデックス数
		subset.materialName = sub.mtrlname; // マテリアル名
		subset.materialIndex = sub.materialindex; // マテリアル配列のインデックス
		subsets.emplace_back(subset);
	}

	// マテリアルデータ作成
	for ( const auto& m : l_materials )
	{
		hft::Material material{};
		material.ambient = hft::HFFLOAT4(
			m.Ambient.r, m.Ambient.g, m.Ambient.b, m.Ambient.a);
		material.diffuse = hft::HFFLOAT4(
			m.Diffuse.r, m.Diffuse.g, m.Diffuse.b, m.Diffuse.a);

		material.specular = hft::HFFLOAT4(
			m.Specular.r, m.Specular.g, m.Specular.b, m.Specular.a);
		material.emission = hft::HFFLOAT4(
			m.Emission.r, m.Emission.g, m.Emission.b, m.Emission.a);
		material.shininess = m.Shininess;

		if ( m.texturename.empty() )
		{
			material.isTexture = FALSE;
			textureNames.emplace_back("");
		}
		else
		{
			material.isTexture = TRUE;
			textureNames.emplace_back(m.texturename);
		}

		materials.emplace_back(material);
	}
}