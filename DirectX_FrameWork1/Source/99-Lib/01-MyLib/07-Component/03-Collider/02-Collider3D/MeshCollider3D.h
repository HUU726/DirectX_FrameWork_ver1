#pragma once

#include "./00-Collider3D/Collider3D.h"
#include "../../../998-FH_Types/Mesh.h"




class MeshCollider3D : public Collider3D
{
private:
	std::shared_ptr<hft::Mesh> sp_mesh;
	std::vector<hft::HFFLOAT3> li_vertexWorldPos;


public:
	MeshCollider3D();
	MeshCollider3D(const std::shared_ptr<hft::Mesh>& _mesh);

	std::shared_ptr<hft::Mesh> GetMesh() { return sp_mesh; }
	std::vector<hft::HFFLOAT3> GetVertexWorldScales() { return li_vertexWorldPos; }

	bool CollideWith(Collider3D* _p_col) override;
	bool CollideWithBox(Collider3D* _p_col) override;
	bool CollideWithSqhere(Collider3D* _p_col) override;
	bool CollideWithMesh(Collider3D* _p_col) override;

	void Init() override;
	void Update() override;

};

