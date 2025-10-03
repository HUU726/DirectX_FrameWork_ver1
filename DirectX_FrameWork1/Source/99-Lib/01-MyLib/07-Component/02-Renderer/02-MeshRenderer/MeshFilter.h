#pragma once

#include <vector>

#include "../../00-Component/Component.h"
#include "../../../04-Texture/Texture.h"
#include "../../../998-FH_Types/Mesh.h"
#include "../../../998-FH_Types/Sprite2D.h"


class MeshFilter : public Component
{
private:
	hft::Mesh* mesh;
	hft::Sprite2D* sprite;


public:
	MeshFilter();
	MeshFilter(hft::Mesh& _mesh);
	MeshFilter(hft::Sprite2D& _sprite);
	~MeshFilter();
	void SetMesh(hft::Mesh* _p_mesh)
	{
		delete mesh;
		mesh = _p_mesh;
	}
	void SetSprite(hft::Sprite2D* _p_sprite)
	{
		delete sprite;
		sprite = _p_sprite;
	}
	hft::Mesh* GetMesh() { return mesh; }
	hft::Sprite2D* GetSprite() { return sprite; }
	//void LoadTexture(const char* _filePath) { mesh->LoadTexture(_filePath); }

	void Init() override;
};

