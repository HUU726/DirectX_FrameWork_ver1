#include "Collider2D.h"

void Collider2D::SetFuncCollisionEnter(CallbackOnCollisionEnter2D _func)
{
	funcOnCollisionEnter = _func;
}

void Collider2D::OnCollisionEnter(Collider2D* _p_col)
{
	if (funcOnCollisionEnter != nullptr)
		funcOnCollisionEnter(_p_col);
}


bool BoxBox(Collider2D* _box1, Collider2D* _box2)
{
	Transform* col1Transform = _box1->GetTransform();
	Transform* col2Transform = _box2->GetTransform();
	glm::vec2 col1Pos = col1Transform->position;
	glm::vec2 col1Size = { col1Transform->scale.x / 2,col1Transform->scale.y / 2 };
	glm::vec2 col2Pos = col2Transform->position;
	glm::vec2 col2Size = { col2Transform->scale.x / 2,col2Transform->scale.y / 2 };

	glm::vec2 col1TopLeft = col1Pos - col1Size;
	glm::vec2 col1BottomRight = col1Pos + col1Size;
	glm::vec2 col2TopLeft = col2Pos - col2Size;
	glm::vec2 col2BottomRight = col2Pos + col2Size;

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
	int CollisionVec = glm::min(glm::min(topCollision, bottomCollision), glm::min(leftCollision, rightCollision));	//ˆê”Ô¬‚³‚¢‚à‚ð‘ã“ü

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
	glm::vec3 col1Pos = _circle1->GetPosition();
	glm::vec3 col2Pos = _circle2->GetPosition();
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
	glm::vec3 boxPos = _box->GetPosition();
	glm::vec3 boxSize = _box->GetSize();
	float top = boxPos.y - (boxSize.y / 2);
	float bottom = boxPos.y + (boxSize.y / 2);
	float left = boxPos.x - (boxSize.x / 2);
	float right = boxPos.x - (boxSize.x / 2);

	glm::vec3 circlePos = _circle->GetPosition();
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
