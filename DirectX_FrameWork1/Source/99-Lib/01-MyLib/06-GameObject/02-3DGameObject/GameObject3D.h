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

	/**
	* @brief	コライダー同士が衝突した際の処理
	* @param	Collider3D*	_p_col	3D用コライダーのポインタ
	*/
	virtual void OnCollisionEnter3D(Collider3D* _p_col) {}
	/**
	* @brief	コライダー同士が離れた際の処理
	* @param	Collider3D*	_p_col	3D用コライダーのポインタ
	*/
	virtual void OnCollisionExit3D(Collider3D* _p_col) {}
	/**
	* @brief	コライダー同士が接触中の処理
	* @param	Collider3D*	_p_col	3D用コライダーのポインタ
	*/
	virtual void OnCollisionStay3D(Collider3D* _p_col) {}

	virtual void OnTriggerEnter3D(Collider3D* _p_col) {}
	virtual void OnTriggerExit3D(Collider3D* _p_col) {}
	virtual void OnTriggerStay3D(Collider3D* _p_col) {}
};