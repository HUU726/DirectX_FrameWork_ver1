#pragma once

#include <vector>

#include "../../00-Component/Component.h"
#include "../../../04-Texture/Texture.h"
#include "../../../998-FH_Types/Mesh.h"
#include "../../../998-FH_Types/Sprite2D.h"

using hft::Mesh;
using hft::Sprite2D;


class MeshFilter : public Component
{
private:
	Mesh* mesh;
	Sprite2D* sprite;


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
	//void LoadTexture(const char* _filePath) { mesh->LoadTexture(_filePath); }

	void Init() override;
};

