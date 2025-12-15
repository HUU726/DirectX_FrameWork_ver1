#pragma once


/**
* @file		Mesh‚ÆMeshRenderer‚ð‚Â‚È‚®‚½‚ß‚ÌƒNƒ‰ƒX
*/


#include <vector>

#include "../../00-Component/Component.h"
#include "../../../04-Texture/Texture.h"
#include "../../../998-FH_Types/Mesh.h"
#include "../../../998-FH_Types/Sprite2D.h"


class MeshFilter : public Component
{
private:
	std::shared_ptr<hft::Mesh> sp_mesh;
	hft::Mesh mesh;

public:
	MeshFilter();
	MeshFilter(hft::Mesh& _mesh);
	~MeshFilter();
	std::shared_ptr<hft::Mesh> SetMesh(std::string _name);
	std::shared_ptr<hft::Mesh> SetMesh(std::shared_ptr<hft::Mesh> _sp_mesh);
	std::shared_ptr<hft::Mesh> const GetMesh() { return sp_mesh; }
	std::shared_ptr<hft::Mesh> LoadModel(const char* _filePath);

	void Init() override;
};

