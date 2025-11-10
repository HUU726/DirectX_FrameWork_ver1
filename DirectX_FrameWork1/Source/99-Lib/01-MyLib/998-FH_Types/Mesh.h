#pragma once


#include "Shape.h"



namespace hft
{
	//サブセット
	struct Subset
	{
		std::string materialName;	//マテリアル名
		unsigned int indexNum;		//インデックス数
		unsigned int vertexNum;		//頂点数
		unsigned int indexBase;		//開始インデックス
		unsigned int vertexBase;	//開始頂点
		unsigned int materialIndex;	//マテリアル番号
	};

	//マテリアル
	struct Material
	{
		HFFLOAT4 ambient;
		HFFLOAT4 diffuse;
		HFFLOAT4 specular;
		HFFLOAT4 emission;
		float shininess;
		bool isTexture;
		bool fake[2];
	};

	struct Mesh : public hft::Shape
	{
		std::vector<Subset> subsets;
		std::vector<Material> materials;
	};

}