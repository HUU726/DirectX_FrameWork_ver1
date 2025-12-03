#pragma once
#include "../GameObject.h"

class Collider2D;

class GameObject2D : public GameObject
{

public:
	GameObject2D();
	void Init() override;
	void Update() override;
	void Draw() override;

	virtual void OnCollisionEnter3D(Collider2D* _p_col) {}
	virtual void OnCollisionExit3D(Collider2D* _p_col) {}
	virtual void OnCollisionStay3D(Collider2D* _p_col) {}

	virtual void OnTriggerEnter3D(Collider2D* _p_col) {}
	virtual void OnTriggerExit3D(Collider2D* _p_col) {}
	virtual void OnTriggerStay3D(Collider2D* _p_col) {}
};

