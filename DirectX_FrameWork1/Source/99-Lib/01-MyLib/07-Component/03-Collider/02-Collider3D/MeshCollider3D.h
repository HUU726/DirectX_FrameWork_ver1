#pragma once

#include "./00-Collider3D/Collider3D.h"
#include "../../../998-FH_Types/Mesh.h"




class MeshCollider3D : public Collider3D
{
private:




public:
	MeshCollider3D();
	MeshCollider3D(const hft::Mesh& _mesh);

	void Init() override;
	void Update() override;

};

