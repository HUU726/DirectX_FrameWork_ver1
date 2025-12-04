#include "MeshCollider3D.h"

#include "../99-ColliderManager/02-Collider3DManager/Collider3DManager.h"
#include "../../../06-GameObject/GameObject.h"
#include "../../../998-FH_Types/TransformMatrix.h"
#include "../../../998-FH_Types/Vector.h"
#include "../../02-Renderer/02-MeshRenderer/MeshRenderer.h"

MeshCollider3D::MeshCollider3D()
{
	sp_mesh = nullptr;
}

MeshCollider3D::MeshCollider3D(const std::shared_ptr<hft::Mesh>& _mesh)
{
	sp_mesh = _mesh;
}

bool MeshCollider3D::CollideWith(Collider3D* _p_col)
{
	return _p_col->CollideWithMesh(this);
}

bool MeshCollider3D::CollideWithBox(Collider3D* _p_col)
{
	return ::BoxMesh(_p_col, this);
}

bool MeshCollider3D::CollideWithSqhere(Collider3D* _p_col)
{
	return ::SqhereMesh(_p_col, this);
}

bool MeshCollider3D::CollideWithMesh(Collider3D* _p_col)
{
	return ::MeshMesh(this, _p_col);
}

void MeshCollider3D::Init()
{
	InitCallbackFunc();
	sp_mesh = gameObject->GetComponent<MeshRenderer>()->GetShape();

	Transform trf = gameObject->GetTransform();
	hft::TransformMatrix matTrf;
	matTrf.ConversionPosition(trf.position);
	matTrf.ConversionRotation(trf.rotation);
	matTrf.ConversionScale(trf.scale);
	DirectX::XMMATRIX matWorld = matTrf.GetMatrixWorld();

	li_vertexWorldPos.resize(sp_mesh->vertices.size());
	for (int i = 0; i < li_vertexWorldPos.size(); i++)
	{
		hft::HFFLOAT3 vertexLocalPos = sp_mesh->vertices[i].position;
		hft::HFFLOAT3 vertexWorldPos = hft::Vector3::Transform(vertexLocalPos, matWorld);
		li_vertexWorldPos[i] = vertexWorldPos;
	}
}

void MeshCollider3D::Update()
{
	Transform transform = gameObject->GetTransform();
	position = transform.position;
	size = transform.scale;
}
