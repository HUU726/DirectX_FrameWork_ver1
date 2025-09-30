#pragma once
#include "../../../00-Component/Component.h"
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

enum COLLISION_STAT
{
	NO_TOUCH,
	TOP_TOUCH,
	BOTTOM_TOUCH,
	LEFT_TOUCH,
	RIGHT_TOUCH,
};

class Collider2D;

typedef std::function<void(Collider2D*)> CallbackOnCollisionEnter2D;

class Collider2D : public Component
{
protected:
	SHAPE_2D shape;			// 形の種類
	hft::HFFLOAT3 offset;		// gameObjectのTransformとのずれ
	hft::HFFLOAT3 position;		// 現在のワールド座標
	hft::HFFLOAT3 size;			// 四角形：ｘ＝横、ｙ＝縦	円：ｘ＝半径	線分：ｘ＝長さ
	
	bool isTrigger = false;	// トリガー
	COLLISION_STAT state;				// 当たっているかどうか
	bool isActive = true;	// 当たり判定を行うかどうか

	CallbackOnCollisionEnter2D funcOnCollisionEnter = nullptr;

public:
	SHAPE_2D GetShape() { return shape; }
	hft::HFFLOAT3 GetSize() { return size; }
	hft::HFFLOAT3 GetOffset() { return offset; }
	bool GetIsTrigger() { return isTrigger; }
	COLLISION_STAT GetState() { return state; }
	bool GetIsActive() { return isActive; }
	CallbackOnCollisionEnter2D GetFuncCollisionEnter() { return funcOnCollisionEnter; }


	void SetSize(hft::HFFLOAT3 _size) { size = _size; }
	void SetOffset(hft::HFFLOAT3 _offset) { offset = _offset; }
	void SetState(COLLISION_STAT _state) { state = _state; }
	void SetFuncCollisionEnter(CallbackOnCollisionEnter2D _func);

	void OnCollisionEnter(Collider2D* _p_col);
	virtual bool CollideWith(Collider2D* _collider) = 0;
	virtual bool CollideWithBox(Collider2D* _box) = 0;
	virtual bool CollideWithCircle(Collider2D* _circle) = 0;
	virtual bool CollideWithLine(Collider2D* _line) = 0;

};


bool BoxBox(Collider2D* _box1, Collider2D* _box2);
bool CircleCircle(Collider2D* _col1, Collider2D* _col2);
bool LineLine(Collider2D* _col1, Collider2D* _col2);
bool BoxCircle(Collider2D* _col1, Collider2D* _col2);
bool BoxLine(Collider2D* _col1, Collider2D* _col2);
bool CircleLine(Collider2D* _col1, Collider2D* _col2);
