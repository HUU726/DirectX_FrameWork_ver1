#include "Collider3D.h"



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

bool SqhereMesh(Collider3D* _sqhere, Collider3D* _mesh)
{
	if (auto sqherePtr = dynamic_cast<SqhereCollider3D*>(_sqhere))
	{
		
		//auto closest = CloasestPointOnTriangle();
	}
	return false;
}

bool MeshMesh(Collider3D* _mesh1, Collider3D* _mesh2)
{
	return false;
}

DirectX::XMFLOAT3 CloasestPointOnTriangle(hft::HFFLOAT3 _posP, hft::HFFLOAT3 _posA, hft::HFFLOAT3 _posB, hft::HFFLOAT3 _posC)
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

