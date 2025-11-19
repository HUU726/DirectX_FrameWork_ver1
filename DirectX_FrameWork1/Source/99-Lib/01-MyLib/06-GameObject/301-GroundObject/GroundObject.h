#pragma once

#include "../02-3DGameObject/GameObject3D.h"
#include "../../998-FH_Types/Vector.h"

class GroundObject : public GameObject3D
{
private:
	int sizeX;	//X•ûŒü–Ê”
	int sizeZ;	//Z•ûŒü–Ê”
	std::vector<hft::Vector3> vectors;

public:
	
	void Init() override;
	void Update() override;
};

