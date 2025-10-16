#pragma once

#include "HF_FLOAT.h"

#include <vector>

#include "../07-Component/01-Transform/Transform.h"

namespace hft 
{
	struct Vertex
	{
		hft::HFFLOAT4 position;
		hft::HFFLOAT4 color;
		hft::HFFLOAT2 uv;
	};

}