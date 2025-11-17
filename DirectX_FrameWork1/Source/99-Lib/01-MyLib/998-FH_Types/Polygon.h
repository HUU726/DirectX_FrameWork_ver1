#pragma once

#include "./Shape.h"
#include "./Mesh.h"

namespace hft
{
	struct Polygon : public Shape
	{
		Material material;
	};
}