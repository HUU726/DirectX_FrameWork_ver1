#pragma once

#include "../../04-Texture/Texture.h"
#include "../Mesh.h"

class StaticMesh : public hft::Mesh
{
private:
	std::vector<std::string> textureNames;
	std::vector<std::shared_ptr<Texture>> textures;

public:
	/*** ÉQÉbÉ^Å[ ***/
	const std::vector<hft::Material>& GetMaterials() { return materials; }
	const std::vector<hft::Subset>& GetSubsets() { return subsets; }
	const std::vector<std::string>& GetTextureNames() { return textureNames; }
	std::vector<std::shared_ptr<Texture>> GetTextures() { return textures; }

	void Load(std::string _filePath, std::string _textureDirectory = "");
};