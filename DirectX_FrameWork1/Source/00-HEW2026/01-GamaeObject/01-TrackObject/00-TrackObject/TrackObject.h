#pragma once

#include "../../../../01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"


class TrackObject : public GameObject2D
{
protected:
	hft::HFFLOAT2 angle;
	hft::HFFLOAT2 moveVec;

	void Slide();

public:
	void SetMoveVec(const hft::HFFLOAT2& _moveVec) { moveVec = _moveVec; }

};