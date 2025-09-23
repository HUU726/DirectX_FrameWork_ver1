#pragma once

#include "../../../../../998-FH_Types/Mesh.h"

using hft::Mesh;

class Cube : public Mesh
{
public:
	Cube();
	Cube(const Transform& _transform);
	Cube(Transform* _p_transform);
	~Cube();
};

