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

	/**
	* @brief	コライダー同士が衝突した際の処理
	* @param	Collider2D*	_p_col	2D用コライダーのポインタ
	*/
	virtual void OnCollisionEnter2D(Collider2D* _p_col) {}
	/**
	* @brief	コライダー同士が離れた際の処理
	* @param	Collider2D*	_p_col	2D用コライダーのポインタ
	*/
	virtual void OnCollisionExit2D(Collider2D* _p_col) {}
	/**
	* @brief	コライダー同士が接触中の処理
	* @param	Collider2D*	_p_col	2D用コライダーのポインタ
	*/
	virtual void OnCollisionStay2D(Collider2D* _p_col) {}

	virtual void OnTriggerEnter2D(Collider2D* _p_col) {}
	virtual void OnTriggerExit2D(Collider2D* _p_col) {}
	virtual void OnTriggerStay2D(Collider2D* _p_col) {}
};

