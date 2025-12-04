#pragma once

#include "../../00-Collider/Collider.h"
#include <functional>
#include <DirectXMath.h>
#include "../../../../998-FH_Types/HF_FLOAT.h"

enum class SHAPE_2D
{
	BOX = 0,
	CIRCLE,
	LINE,
	ALL_COLLIDER,
};

enum COLLISION_STATE
{
	NO_TOUCH,
	TOP_TOUCH,
	BOTTOM_TOUCH,
	LEFT_TOUCH,
	RIGHT_TOUCH,
};

class Collider2D;
typedef std::function<void(Collider2D*)> CallbackOnCollisionEnter2D;

class Collider2D : public Collider
{
protected:
	SHAPE_2D shape;				// 形の種類
	hft::HFFLOAT3 position;		// 現在のワールド座標
	COLLISION_STATE state;		// 当たっているかどうか

public:
	Collider2D();
	~Collider2D();

	SHAPE_2D GetShape() const { return shape; }
	COLLISION_STATE GetState() const { return state; }
	void SetState(COLLISION_STATE _state) { state = _state; }

	/**
	* @brief	自身と当たり判定
	*/
	virtual bool CollideWith(Collider2D* _collider) = 0;
	/**
	* @brief	自身とBoxColliderとの当たり判定
	*/
	virtual bool CollideWithBox(Collider2D* _box) = 0;
	/**
	* @brief	自身とCircleColliderとの当たり判定
	*/
	virtual bool CollideWithCircle(Collider2D* _circle) = 0;
	/**
	* @brief	自身と線の当たり判定
	*/
	virtual bool CollideWithLine(Collider2D* _line) = 0;

};


bool BoxBox(Collider2D* _box1, Collider2D* _box2);
bool CircleCircle(Collider2D* _col1, Collider2D* _col2);
bool LineLine(Collider2D* _col1, Collider2D* _col2);
bool BoxCircle(Collider2D* _col1, Collider2D* _col2);
bool BoxLine(Collider2D* _col1, Collider2D* _col2);
bool CircleLine(Collider2D* _col1, Collider2D* _col2);
