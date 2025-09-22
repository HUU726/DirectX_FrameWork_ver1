#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

#include "Component.h"
#include "texture.h"
#include "Transform.h"
#include "Vertex.h"
#include "Sprite2D.h"

class Mesh
{
protected:
	Transform* transform;	// 座標・回転・スケール
	bool isCreate = false;	// トランスフォームを動的生成したか
	glm::mat4 worldMatrix;	// ワールド行列
	std::vector<Vertex> vertices;	// 頂点データを格納する
	std::vector<GLushort> indices;	// インデックスデータを格納する
	Texture texture;				// テクスチャー

public:
	Mesh() = default;

	const glm::mat4& GetWorldMatrix() { updateWorldMatrix(); return worldMatrix; }
	std::vector<Vertex>& GetVertices() { return vertices; }
	std::vector<GLushort>& GetIndices() { return indices; }
	bool GetIsCreate() { return isCreate; }
	void AddVertex(const Vertex& _vertex) { vertices.push_back(_vertex); }
	void AddIndex(GLushort index) { indices.push_back(index); }

	void updateWorldMatrix();
	void CreateTransform();
	void setTransform(const Transform& _transform);
	void setTransform(Transform* _p_transform);
	void LoadTexture(const char* _filePath);
	void SetTexture(GLuint _shaderID);
	void SetColor(glm::vec4 _color);

	const Transform& GetTransform() { return *transform; }

};

class MeshFilter : public Component
{
private:
	Mesh* mesh;
	Sprite2D* sprite;

	GEN_COMPONENT_ID(MeshFilter)

public:
	MeshFilter();
	MeshFilter(Mesh& _mesh);
	MeshFilter(Sprite2D& _sprite);
	~MeshFilter();
	void SetMesh(Mesh* _p_mesh)
	{
		delete mesh;
		mesh = _p_mesh;
	}
	void SetSprite(Sprite2D* _p_sprite)
	{
		delete sprite;
		sprite = _p_sprite;
	}
	Mesh* GetMesh() { return mesh; }
	Sprite2D* GetSprite() { return sprite; }
	void LoadTexture(const char* _filePath) { mesh->LoadTexture(_filePath); }

	void Init() override;
};

