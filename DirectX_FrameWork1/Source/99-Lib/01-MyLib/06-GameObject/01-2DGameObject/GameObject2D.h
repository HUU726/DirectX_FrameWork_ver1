#pragma once
#include "../GameObject.h"
#include "../../07-Component/03-Collider/01-Collider2D/00-Collider2D/Collider2D.h"

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

