#pragma once

#include "../02-3DGameObject/GameObject3D.h"

class GroundObject : public GameObject3D
{
private:
	int sizeX;	//X•ûŒü–Ê”
	int sizeZ;	//Z•ûŒü–Ê”


public:
	
	void Init() override;
	void Update() override;
};

