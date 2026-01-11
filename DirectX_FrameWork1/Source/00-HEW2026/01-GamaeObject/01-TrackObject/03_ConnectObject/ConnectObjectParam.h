#pragma once
#include "../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"

//連結ブロックのパラメータ

namespace ConnectObjectParam
{
	//検査用コライダーのパラメータ

	//コライダーの長さ（マス数）
	//6の場合上3マス、下3マス
	const int   searchCollCell = 14;	 

	const float searchCollThickness	 = 40.f; //コライダーの厚み
}