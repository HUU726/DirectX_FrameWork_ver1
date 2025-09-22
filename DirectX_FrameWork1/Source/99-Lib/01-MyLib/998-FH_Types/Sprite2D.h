#pragma once


#include "Vertex.h"


namespace hft {

	struct Sprite2D
	{
		Transform* p_transform;
		bool isCreate;

		std::vector<hft::Vertex> vertices;
		std::vector<unsigned int> indices;
	};

}


