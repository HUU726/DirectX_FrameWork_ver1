#pragma once

#include "../../06-GameObject/GameObject.h"
#include "../../998-FH_Types/StaticMesh/StaticMesh.h"
#include "../../../02-ExternalLib/stringUtility/utility.h"


class TestModel : public GameObject
{
private:
	std::shared_ptr<StaticMesh> sp_staticMesh;


public:

	std::shared_ptr<StaticMesh> GetMesh() { return sp_staticMesh; }
	
	void Init() override;
	void Update() override;
	void Draw() override;
};

