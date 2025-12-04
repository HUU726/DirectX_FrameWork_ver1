#pragma once

#include "../999-Shader/00-Shader/Shader.h"
#include "HF_FLOAT.h"


namespace hft
{
	//ƒ}ƒeƒŠƒAƒ‹
	struct Material
	{
		HFFLOAT4 ambient;
		HFFLOAT4 diffuse = { 1,1,1,1 };
		HFFLOAT4 specular;
		HFFLOAT4 emission;
		float shininess;
		int isTexture;

		Shader shader;
		//std::shared_ptr<Texture> sp_texture;
	};
}