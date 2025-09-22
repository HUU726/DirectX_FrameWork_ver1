#include "Mesh.h"
#include "Cube.h"

void Mesh::updateWorldMatrix()
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), transform->position);	// 位置の変換  

	// DegreeをRadianに変換  
	float radX = glm::radians(transform->rotation.x);
	float radY = glm::radians(transform->rotation.y);
	float radZ = glm::radians(transform->rotation.z);

	// 回転の変換（オイラー角を使用）  
	glm::mat4 rotation = glm::mat4(1.0f);	// 単位行列で初期化  
	rotation = glm::rotate(rotation, radX, glm::vec3(1.0f, 0.0f, 0.0f));	// X軸周りの回転  
	rotation = glm::rotate(rotation, radY, glm::vec3(0.0f, 1.0f, 0.0f));	// Y軸周りの回転  
	rotation = glm::rotate(rotation, radZ, glm::vec3(0.0f, 0.0f, 1.0f));	// Z軸周りの回転  
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform->scale);	// スケールの変換  
	worldMatrix = translation * rotation * scale;	// ワールド変換行列の計算  
}

void Mesh::CreateTransform()
{
	if (transform == nullptr)
	{
		transform = new	Transform;
		isCreate = true;
	}
}

void Mesh::setTransform(const Transform& _transform)
{
	if (transform != nullptr)
	{
		transform->position = _transform.position;
		transform->rotation = _transform.rotation;
		transform->scale = _transform.scale;
	}
}

void Mesh::setTransform(Transform* _p_transform)
{
	if (transform != nullptr && transform != _p_transform)
	{
		if (isCreate)
			delete transform;
		transform = nullptr;
	}

	if (transform != _p_transform)
	{
		if (_p_transform->getGameObject() != nullptr)
		{
			transform = _p_transform;
		}
		else
		{
			transform->position = _p_transform->position;
			transform->rotation = _p_transform->rotation;
			transform->scale = _p_transform->scale;
		}
		isCreate = false;
	}
}

void Mesh::LoadTexture(const char* _filePath)
{
	texture.LoadTexture(_filePath);
}

void Mesh::SetTexture(GLuint _shaderID)
{
	texture.SetTexture(_shaderID);
}

void Mesh::SetColor(glm::vec4 _color)
{
	for (auto& vertex : vertices)
		vertex.color = _color;
}




/********************************************************
*		MeshFilter
********************************************************/
#include "GameObject.h"

MeshFilter::MeshFilter()
{
	mesh = new Cube;
	sprite = nullptr;
}

MeshFilter::MeshFilter(Mesh& _mesh)
{
	mesh = new Mesh;
	*mesh = _mesh;
	sprite = nullptr;
}

MeshFilter::MeshFilter(Sprite2D& _sprite)
{
	sprite = new Sprite2D;
	
	mesh = nullptr;
	*sprite = _sprite;
}

MeshFilter::~MeshFilter()
{
	if (mesh != nullptr)
	{
		delete mesh;
		mesh = nullptr;
	}
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void MeshFilter::Init()
{
	if (mesh != nullptr)
	{
		Transform* transform = &gameObject->GetTransform();
		if (mesh->GetIsCreate())
		{
			transform->position = mesh->GetTransform().position;
			transform->rotation = mesh->GetTransform().rotation;
			transform->scale = mesh->GetTransform().scale;
		}
		mesh->setTransform(transform);
	}
	
	if (sprite != nullptr)
	{
		Transform* transform = &gameObject->GetTransform();
		if (sprite->GetIsCreate())
		{
			transform->position = sprite->getTransform().position;
			transform->rotation = sprite->getTransform().rotation;
			transform->scale = sprite->getTransform().scale;
		}
		sprite->setTransform(transform);
	}
}