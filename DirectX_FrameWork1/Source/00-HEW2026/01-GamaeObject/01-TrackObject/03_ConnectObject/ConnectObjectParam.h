#pragma once
#include "../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"

//連結ブロックのパラメータ
namespace ConnectObjectParam
{
	//本体のパラメータ
	const hft::HFFLOAT3 mainBodyScale = { 80.f, 80.f, 1.f };
	const char* mainBodyTexName = "Assets/01-Texture/03-Enemy/EighthNote_Under.png";

	//検査用コライダーのパラメータ
	const float searchCollCellSize = 100.f;
	const int   searchCollCellCount = 14;//コライダーの長さ（マス数）　6の場合上3マス、下3マス
	const float searchCollThickness	 = 20.f; //コライダーの厚み


	//攻撃用オブジェクトのパラメータ
	const char* emitAttackTexName = "Assets/01-Texture/03-Enemy/Connect_V.png";
	const float emitAttacktTexThickness = 500.f; //攻撃判定用の画像の幅

	const hft::HFFLOAT3 emitAttackVertRotation = { 0.f, 0.f, 90.f }; //横に繋がった時の画像の向き
	const hft::HFFLOAT3 emitAttackHoriRotation = { 0.f, 0.f,  0.f }; //縦に繋がった時の画像の向き
	const float emitAttackCollThickness = 20.f; //攻撃判定用の画像の幅
}