#pragma once

#include "HF_FLOAT.h"

namespace hft
{
	struct Material
	{
		HFFLOAT4 ambient;
		HFFLOAT4 diffuse;
		HFFLOAT4 specular;
		HFFLOAT4 emission;
		bool isTexture;
		bool fake[2];
	};
}
