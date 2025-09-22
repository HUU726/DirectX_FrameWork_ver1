#pragma once


#include "Vertex.h"



namespace hft
{

	struct Mesh
	{
		Transform* p_transform;
		bool isCreate;

		std::vector<hft::Vertex> vertices;
		std::vector<unsigned int> indices;
	};

}