#pragma once

#include "../../../../01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"


class TrackObject : public GameObject2D
{
protected:
	hft::HFFLOAT2 lineIndex;	//マップ上のどのマスにいるか
	hft::HFFLOAT2 angle;		//どの方向をむいているのか

public:
	void SetLineIndex(const hft::HFFLOAT2& _index) { lineIndex = _index; }
	hft::HFFLOAT2 GetLineIndex() { return lineIndex; }
};