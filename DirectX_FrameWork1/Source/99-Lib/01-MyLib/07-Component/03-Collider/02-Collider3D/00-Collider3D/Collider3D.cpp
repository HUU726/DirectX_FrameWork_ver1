#include "Collider3D.h"


#include "../../99-ColliderManager/02-Collider3DManager/Collider3DManager.h"

#include "../../../99-CompMng/ComponentManager.h"


Collider3D::Collider3D()
{
	ComponentManager<Collider3D>::GetInstance().Add(this);
	Collider3DManager::GetInstance().AddCollider(this);
}

Collider3D::~Collider3D()
{
	ComponentManager<Collider3D>::GetInstance().Remove(this);
}

void Collider3D::SetFuncCollisionEnter(CallbackOnCollisionEnter3D _func)
{
	funcOnCollisionEnter = _func;
}


void Collider3D::OnCollisionEnter3D(Collider3D* _p_col)
{
	if (funcOnCollisionEnter != nullptr)
		funcOnCollisionEnter(_p_col);
}





#include "../../../../998-FH_Types/Mesh.h"
#include "../BoxCollider3D.h"
#include "../SqhereCollider3D.h"
#include "../MeshCollider3D.h"
#include "../../../../06-GameObject/GameObject.h"
#include "../../../../998-FH_Types/Vector.h"


bool BoxBox(Collider3D* _box1, Collider3D* _box2)
{
	return false;
}

bool BoxSqhere(Collider3D* _box, Collider3D* _sqhere)
{
	return false;
}

bool BoxMesh(Collider3D* _box, Collider3D* _mesh)
{
	return false;
}

bool SqhereSqhere(Collider3D* _sqhere1, Collider3D* _sqhere2)
{
	return false;
}

/**
* @brief	球体とメッシュ(Polygon)の当たり判定
* @param	Collider3D*		_sqhere		球体
* @param	Collider3D*		_mesh		メッシュ(三角形ポリゴン)
*/
bool SqhereMesh(Collider3D* _sqhere, Collider3D* _mesh)
{
	auto sqherePtr = dynamic_cast<SqhereCollider3D*>(_sqhere);
	if (!sqherePtr)
	{
		return false;
	}

	auto meshPtr = dynamic_cast<MeshCollider3D*>(_mesh);
	if (!meshPtr)
	{
		return false;
	}

	hft::HFFLOAT4 sqherePos = sqherePtr->GetGameObject()->GetTransform().position;
	float r = sqherePtr->GetRadius();

	auto sp_mesh = meshPtr->GetMesh();
	auto vertices = sp_mesh->vertices;
	auto indices = sp_mesh->indices;

	for ( int i = 0; i < indices.size() - 3; i+=3 )
	{
		hft::HFFLOAT3 posA = vertices[indices[i + 0]].position;
		hft::HFFLOAT3 posB = vertices[indices[i + 1]].position;
		hft::HFFLOAT3 posC = vertices[indices[i + 2]].position;

		hft::HFFLOAT3 nearPos = CloasestPointOnTriangle(sqherePos, posA, posB, posC);

		float dx = nearPos.x - sqherePos.x;
		float dy = nearPos.y - sqherePos.y;
		float dz = nearPos.z - sqherePos.z;

		float  distance  = dx * dx + dy * dy + dz * dz;
		
		if ( distance <= r * r )
		{
			return true;
		}
	}

	
	//auto closest = CloasestPointOnTriangle();
	return false;
}

bool MeshMesh(Collider3D* _mesh1, Collider3D* _mesh2)
{
	return false;
}

hft::HFFLOAT3 CloasestPointOnTriangle(hft::HFFLOAT3 _posP, hft::HFFLOAT3 _posA, hft::HFFLOAT3 _posB, hft::HFFLOAT3 _posC)
{

	//辺のベクトルをとる
	hft::HFFLOAT3 AB = _posB - _posA;
	hft::HFFLOAT3 AC = _posC - _posA;

	//頂点Aから点P
	// へのベクトルをとる
	hft::HFFLOAT3 AP = _posP - _posA;
	float d1 = hft::Dot(AB, AP);
	float d2 = hft::Dot(AC, AP);

	//頂点Aが最短か
	if (d1 <= 0.0f && d2 <= 0.0f)
		return _posA;


	//頂点Bから点Pへののベクトルをとる
	hft::HFFLOAT3 BP = _posP - _posB;
	float d3 = hft::Dot(AB, BP);
	float d4 = hft::Dot(AC, BP);

	//頂点Bが最短か
	if (d3 >= 0.0f && d4 <= d3)
		return _posB;

	
	float vc = d1 * d4 - d3 * d2;

	//辺AB
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		hft::HFFLOAT3 result = _posA + AB * v;
		return result;
	}


	//頂点Cから点Pへのベクトルをとる
	hft::HFFLOAT3 CP = _posP - _posC;
	float d5 = hft::Dot(AB, CP);
	float d6 = hft::Dot(AC, CP);

	//頂点Cが最短か
	if (d6 >= 0.0f && d5 <= d6)
		return _posC;

	
	float vb = d5 * d2 - d1 * d6;

	//辺AC
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		hft::HFFLOAT3 result = _posA + AC * w;
		return result;
	}

	
	float va = d3 * d6 - d5 * d4;

	//辺BC
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		hft::HFFLOAT3 BC = _posC - _posB;
		hft::HFFLOAT3 result = _posB + BC * w;
		return result;
	}


	//三角形内部
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	hft::HFFLOAT3 result = _posA + (AB * v + AC * w);
	return result;

}

