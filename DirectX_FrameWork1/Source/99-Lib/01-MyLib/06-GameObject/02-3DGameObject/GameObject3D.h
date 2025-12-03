#pragma once
#include "../GameObject.h"


class Collider3D;

class GameObject3D : public GameObject
{
private:


public:
	GameObject3D();
	void Init() override;
	void Update() override;
	void Draw() override;

	virtual void OnCollisionEnter3D(Collider3D* _p_col) {}
	virtual void OnCollisionExit3D(Collider3D* _p_col) {}
	virtual void OnCollisionStay3D(Collider3D* _p_col) {}

	virtual void OnTriggerEnter3D(Collider3D* _p_col) {}
	virtual void OnTriggerExit3D(Collider3D* _p_col) {}
	virtual void OnTriggerStay3D(Collider3D* _p_col) {}
};