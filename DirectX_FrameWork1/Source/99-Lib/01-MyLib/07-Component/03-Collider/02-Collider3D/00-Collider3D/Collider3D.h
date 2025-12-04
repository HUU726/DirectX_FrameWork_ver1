#pragma once

#include "../../00-Collider/Collider.h"


class Collider3D : public Collider
{
protected:
	hft::HFFLOAT3 position;	//座標


public:
	Collider3D();
	~Collider3D();

	hft::HFFLOAT3 GetPosition() const { return position; }
	void SetPosition(hft::HFFLOAT3 _pos) { position = _pos; }

	virtual bool CollideWith(Collider3D* _p_col) = 0;
	virtual bool CollideWithBox(Collider3D* _p_col) = 0;
	virtual bool CollideWithSqhere(Collider3D* _p_col) = 0;
	virtual bool CollideWithMesh(Collider3D* _p_col) = 0;
			
};


bool BoxBox(Collider3D* _box1, Collider3D* _box2);
bool BoxSqhere(Collider3D* _box, Collider3D* _sqhere);
bool BoxMesh(Collider3D* _box, Collider3D* _mesh);
bool SqhereSqhere(Collider3D* _sqhere1, Collider3D* _sqhere2);
bool SqhereMesh(Collider3D* _sqhere, Collider3D* _mesh);
bool MeshMesh(Collider3D* _mesh1, Collider3D* _mesh2);

/**
* @brief	基点と三角形を並べたとき、三角形上の一番近い座標を返す
* @param	hft::HFFLOAT3	_posP	基点
* @param	hft::HFFLOAT3	_posA	頂点A
* @param	hft::HFFLOAT3	_posA	頂点B
* @param	hft::HFFLOAT3	_posA	頂点C
* @return	hft::HFFLOAT3	最近地
*/
hft::HFFLOAT3 CloasestPointOnTriangle(hft::HFFLOAT3 _posP, hft::HFFLOAT3 _posA, hft::HFFLOAT3 _posB, hft::HFFLOAT3 _posC);