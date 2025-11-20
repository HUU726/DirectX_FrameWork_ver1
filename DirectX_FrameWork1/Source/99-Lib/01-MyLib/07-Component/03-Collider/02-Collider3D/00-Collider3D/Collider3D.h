#pragma once
#include "../../../00-Component/Component.h"
#include "../../../../998-FH_Types/HF_FLOAT.h"
#include <functional>

class Collider3D;

typedef std::function<void(Collider3D*)> CallbackOnCollisionEnter3D;

class Collider3D : public Component
{
protected:
	hft::HFFLOAT3 offset;	//オブジェクトとのずれは場
	hft::HFFLOAT3 position;	//座標
	hft::HFFLOAT3 size;		//当たり判定のスケース

	bool isTrigger;
	CallbackOnCollisionEnter3D funcOnCollisionEnter = nullptr;	

public:
	hft::HFFLOAT3 GetOffset() { return offset; }
	hft::HFFLOAT3 GetPosition() { return offset; }
	hft::HFFLOAT3 GetSize() { return size; }
	bool GetIsTrigger() { return isTrigger; }
	bool GetIsAction() { return isActive; }
	CallbackOnCollisionEnter3D GetFuncCollisionEnter() { return funcOnCollisionEnter; }

	void SetOffset(hft::HFFLOAT3 _offset) { offset = _offset; }
	void SetPosition(hft::HFFLOAT3 _pos) { position = _pos; }
	void SetSize(hft::HFFLOAT3 _size) { size = _size; };
	void SetFuncCollisionEnter(CallbackOnCollisionEnter3D _func);

	void OnCollisionEnter3D(Collider3D* _p_col);
	virtual bool CollideWith(Collider3D* _p_col) = 0;
	virtual bool CollideWithBox(Collider3D* _p_col) = 0;
	virtual bool CollideWithSqhere(Collider3D* _p_col) = 0;
	virtual bool CollideWithMesh(Collider3D* _p_col) = 0;

};

class BoxCollider3D;
class SqhereCollider3D;
class MeshCollider3D;

bool BoxBox(Collider3D* _box1, Collider3D* _box2);
bool BoxSqhere(Collider3D* _box, Collider3D* _sqhere);
bool BoxMesh(Collider3D* _box, Collider3D* _mesh);
bool SqhereSqhere(Collider3D* _sqhere1, Collider3D* _sqhere2);
bool SqhereMesh(Collider3D* _sqhere, Collider3D* _mesh);
bool MeshMesh(Collider3D* _mesh1, Collider3D* _mesh2);

DirectX::XMFLOAT3 CloasestPointOnTriangle(hft::HFFLOAT3 _posP, hft::HFFLOAT3 _posA, hft::HFFLOAT3 _posB, hft::HFFLOAT3 _posC);