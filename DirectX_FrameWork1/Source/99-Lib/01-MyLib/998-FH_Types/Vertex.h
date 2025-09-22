#pragma once

#include <DirectXMath.h>

#include <vector>

#include "../07-Component/01-Transform/Transform.h"

namespace hft 
{
	struct Vertex
	{
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 uv;
	};

}