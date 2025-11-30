#include "Collider2D.h"

#define NOMINMAX
#include <DirectXMath.h>
#include <algorithm>

#include "../../../../06-GameObject/GameObject.h"
#include "../../../01-Transform/Transform.h"
#include "../../../../998-FH_Types/HF_FLOAT.h"

#include "../../99-ColliderManager/01-Collider2DManager/Collider2DManager.h"

#include "../../../99-CompMng/ComponentManager.h"

Collider2D::Collider2D()
{
	Collider2DManager::GetInstance().AddCollider(this);
	ComponentManager<Collider2D>::GetInstance().Add(this);
}

Collider2D::~Collider2D()
{
	ComponentManager<Collider2D>::GetInstance().Remove(this);
}

void Collider2D::SetFuncCollisionEnter(CallbackOnCollisionEnter2D _func)
{
	funcOnCollisionEnter = _func;
}

void Collider2D::OnCollisionEnter2D(Collider2D* _p_col)
{
	if (funcOnCollisionEnter != nullptr)
		funcOnCollisionEnter(_p_col);
}


bool BoxBox(Collider2D* _box1, Collider2D* _box2)
{
	Transform* col1Transform = _box1->GetGameObject()->GetTransformPtr();
	Transform* col2Transform = _box2->GetGameObject()->GetTransformPtr();
	hft::HFFLOAT2 col1Pos = { col1Transform->position.x,col1Transform->position.y };
	hft::HFFLOAT2 col1Size = { col1Transform->scale.x / 2,col1Transform->scale.y / 2 };
	hft::HFFLOAT2 col2Pos = { col2Transform->position.x,col2Transform->position.y };
	hft::HFFLOAT2 col2Size = { col2Transform->scale.x / 2,col2Transform->scale.y / 2 };

	hft::HFFLOAT2 col1TopLeft = col1Pos - col1Size;

	hft::HFFLOAT2 col1BottomRight = col1Pos + col1Size;
	hft::HFFLOAT2 col2TopLeft = col2Pos - col2Size;
	hft::HFFLOAT2 col2BottomRight = col2Pos + col2Size;

	if (!(col1TopLeft.x < col2BottomRight.x &&
		col1BottomRight.x > col2TopLeft.x &&
		col1TopLeft.y < col2BottomRight.y &&
		col1BottomRight.y > col2TopLeft.y))
	{
		_box1->SetState(NO_TOUCH);
		_box2->SetState(NO_TOUCH);
		return false;
	}
	int topCollision = col2BottomRight.y - col1TopLeft.y;		//ã‘¤
	int bottomCollision = col1BottomRight.y - col2TopLeft.y;	//‰º‘¤
	int leftCollision = col2BottomRight.x - col1TopLeft.x;		//¶‘¤
	int rightCollision = col1BottomRight.x - col2TopLeft.x;		//‰E‘¤
	int CollisionVec = std::min(std::min(topCollision, bottomCollision), std::min(leftCollision, rightCollision));	//ˆê”Ô¬‚³‚¢‚à‚ð‘ã“ü

	if (CollisionVec == topCollision)
	{
		_box1->SetState(TOP_TOUCH);
		_box2->SetState(BOTTOM_TOUCH);
	}
	else if (CollisionVec == bottomCollision)
	{
		_box1->SetState(BOTTOM_TOUCH);
		_box2->SetState(TOP_TOUCH);
	}
	else if (CollisionVec == rightCollision)
	{
		_box1->SetState(RIGHT_TOUCH);
		_box2->SetState(LEFT_TOUCH);
	}
	else if (CollisionVec == leftCollision)
	{
		_box1->SetState(LEFT_TOUCH);
		_box2->SetState(RIGHT_TOUCH);
	}

	return true;
}

bool CircleCircle(Collider2D* _circle1, Collider2D* _circle2)
{
	hft::HFFLOAT3 col1Pos = _circle1->GetGameObject()->GetTransform().position;
	hft::HFFLOAT3 col2Pos = _circle2->GetGameObject()->GetTransform().position;
	float col1R = _circle1->GetSize().x;
	float col2R = _circle2->GetSize().x;

	float distance = (col1Pos.x - col2Pos.x) * (col1Pos.x - col2Pos.x) + (col1Pos.y - col2Pos.y) * (col1Pos.y - col2Pos.y);
	float collisionDistans = (col1R * col1R) + (col2R * col2R);

	if (collisionDistans >= distance)
	{
		_circle1->SetState(TOP_TOUCH);
		_circle2->SetState(TOP_TOUCH);
		return true;
	}
	_circle1->SetState(NO_TOUCH);
	_circle2->SetState(NO_TOUCH);
	return false;
}

bool LineLine(Collider2D* _col1, Collider2D* _col2)
{
	return false;
}

bool BoxCircle(Collider2D* _box, Collider2D* _circle)
{
	hft::HFFLOAT3 boxPos = _box->GetGameObject()->GetTransform().position;
	hft::HFFLOAT3 boxSize = _box->GetSize();
	float top = boxPos.y - (boxSize.y / 2);
	float bottom = boxPos.y + (boxSize.y / 2);
	float left = boxPos.x - (boxSize.x / 2);
	float right = boxPos.x - (boxSize.x / 2);

	hft::HFFLOAT3 circlePos = _circle->GetGameObject()->GetTransform().position;
	float closestX = std::max(left, std::min(circlePos.x, right));
	float closestY = std::max(bottom, std::min(circlePos.y, top));

	float dx = circlePos.x - closestX;
	float dy = circlePos.y - closestY;

	float disLength = dx * dx + dy * dy;
	float r = _circle->GetSize().x;

	if (disLength <= (r * r))
	{
		_box->SetState(TOP_TOUCH);
		_circle->SetState(TOP_TOUCH);
		return true;
	}
	_box->SetState(NO_TOUCH);
	_circle->SetState(NO_TOUCH);
	return false;
}

bool BoxLine(Collider2D* _col1, Collider2D* _col2)
{
	return false;
}

bool CircleLine(Collider2D* _col1, Collider2D* _col2)
{
	return false;
}
