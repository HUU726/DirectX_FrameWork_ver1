#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include "Transform.h"
#include <functional>

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
//引数と戻り値が同じ八の関数名がSceneInitという名前
typedef std::function<void(Collider2D*)> CallbackOnCollisionEnter2D;

class Collider2D : public Component
{
protected:
	SHAPE_2D shape;			// 形の種類
	Transform* transform;	// gameObjectのTransform
	glm::vec3 offset;		// gameObjectのTransformとのずれ
	glm::vec3 position;		// 現在のワールド座標
	glm::vec3 size;			// 四角形：ｘ＝横、ｙ＝縦	円：ｘ＝半径	線分：ｘ＝長さ
	
	bool isTrigger = false;	// トリガー
	COLLISION_STAT state;				// 当たっているかどうか
	bool isActive = true;	// 当たり判定を行うかどうか

	CallbackOnCollisionEnter2D funcOnCollisionEnter = nullptr;

public:
	SHAPE_2D GetShape() { return shape; }
	Transform* GetTransform() { return transform; }
	glm::vec3 GetPosition() { return transform->position; }
	glm::vec3 GetSize() { return size; }
	glm::vec3 GetOffset() { return offset; }
	bool GetIsTrigger() { return isTrigger; }
	COLLISION_STAT GetState() { return state; }
	bool GetIsActive() { return isActive; }
	CallbackOnCollisionEnter2D GetFuncCollisionEnter() { return funcOnCollisionEnter; }


	void SetSize(glm::vec3 _size) { size = _size; }
	void SetOffset(glm::vec3 _offset) { offset = _offset; }
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
