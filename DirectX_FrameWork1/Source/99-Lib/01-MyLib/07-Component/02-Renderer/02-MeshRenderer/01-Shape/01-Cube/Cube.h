#pragma once
#include "Mesh.h"

class Cube : public Mesh
{
public:
	Cube();
	Cube(const Transform& _transform);
	Cube(Transform* _p_transform);
	~Cube();
};

