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


#include "../BoxCollider2D.h"
#include "../CircleCollider2D.h"

bool BoxBox(Collider2D* _box1, Collider2D* _box2)
{
	auto box1 = dynamic_cast<BoxCollider2D*>(_box1);
	auto box2 = dynamic_cast<BoxCollider2D*>(_box2);

	hft::HFFLOAT3 box1Pos = box1->GetGameObject()->GetTransform().position;
	box1Pos += box1->GetOffset();
	hft::HFFLOAT3 box1Size = box1->GetSize();

	hft::HFFLOAT3 box2Pos = box2->GetGameObject()->GetTransform().position;
	box2Pos += box2->GetOffset();
	hft::HFFLOAT3 box2Size = box2->GetSize();

	hft::HFFLOAT2 col1TopLeft = { box1Pos.x - box1Size.x,box1Pos.y + box1Size.y };
	hft::HFFLOAT2 col1BottomRight = { box1Pos.x + box1Size.x,box1Pos.y - box1Size.y };
	hft::HFFLOAT2 col2TopLeft = { box2Pos.x - box2Size.x,box2Pos.y + box2Size.y };
	hft::HFFLOAT2 col2BottomRight = { box2Pos.x + box2Size.x,box2Pos.y - box2Size.y };

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
	auto circle1 = dynamic_cast<CircleCollider2D*>(_circle1);
	auto circle2 = dynamic_cast<CircleCollider2D*>(_circle2);

	hft::HFFLOAT3 col1Pos = circle1->GetGameObject()->GetTransform().position;
	hft::HFFLOAT3 col2Pos = circle2->GetGameObject()->GetTransform().position;

	col1Pos += circle1->GetOffset();
	col2Pos += circle2->GetOffset();

	float col1R = circle1->GetRadius();
	float col2R = circle2->GetRadius();

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
	auto box = dynamic_cast<BoxCollider2D*>(_box);
	auto circle = dynamic_cast<CircleCollider2D*>(_circle);

	hft::HFFLOAT3 boxPos = box->GetGameObject()->GetTransform().position;
	hft::HFFLOAT3 circlePos = circle->GetGameObject()->GetTransform().position;

	boxPos += box->GetOffset();
	circlePos += circle->GetOffset();

	hft::HFFLOAT3 boxSize = box->GetSize();
	float radius = circle->GetRadius();

	boxSize /= 2.f;
	float top = boxPos.y - boxSize.y;
	float bottom = boxPos.y + boxSize.y;
	float left = boxPos.x - boxSize.x;
	float right = boxPos.x - boxSize.x;

	float closestX = std::max(left, std::min(circlePos.x, right));
	float closestY = std::max(bottom, std::min(circlePos.y, top));

	float dx = circlePos.x - closestX;
	float dy = circlePos.y - closestY;

	float disLength = dx * dx + dy * dy;
	float radiusLength = radius * radius;

	if (disLength <= radiusLength)
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
