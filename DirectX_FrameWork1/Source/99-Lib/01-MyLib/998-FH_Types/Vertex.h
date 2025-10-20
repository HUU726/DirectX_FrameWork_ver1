#pragma once

#include "HF_FLOAT.h"

#include <vector>

#include "../07-Component/01-Transform/Transform.h"

namespace hft 
{
	struct Vertex
	{
		hft::HFFLOAT3 position;
		hft::HFFLOAT3 normal;
		hft::HFFLOAT4 color;
		hft::HFFLOAT2 uv;
	};

}