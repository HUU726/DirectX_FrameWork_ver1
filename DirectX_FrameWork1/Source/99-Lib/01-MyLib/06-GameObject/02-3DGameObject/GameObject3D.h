#pragma once
#include "../GameObject.h"


#include "../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"
#include "../../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../../07-Component/03-Collider/02-Collider3D/BoxCollider3D.h"
#include "../../07-Component/03-Collider/02-Collider3D/SqhereCollider3D.h"
#include "../../07-Component/03-Collider/02-Collider3D/MeshCollider3D.h"

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