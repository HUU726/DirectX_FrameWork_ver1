#pragma once

#include "./Shape.h"
#include "./Material.h"

namespace hft
{
	struct Polygon : public Shape
	{
		Material material;
	};
}