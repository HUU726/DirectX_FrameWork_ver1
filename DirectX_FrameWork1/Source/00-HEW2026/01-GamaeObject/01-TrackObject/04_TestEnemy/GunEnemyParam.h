#pragma once

#include "../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"

namespace GunEnemyParam
{
	const int waittimer = 180;	// 弾が消えてからの待機時間
	const int shot = 10;		// シューティングのフレーム数
	const hft::HFFLOAT3 scale = { 50.f,50.f,50.f };		// サイズ
	const hft::HFFLOAT3 position = { 0.0f,0.0f, -2.0f };	// 位置
	const char* biteenemyTexName = "Assets/01-Texture/99-Test/daruma.jpg";	// テクスチャ
}