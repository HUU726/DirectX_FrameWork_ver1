#pragma once
#include"../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"

namespace BiteEnemyParam
{
	const int hitstoptime = 10;	// ヒットストップ時間
	const hft::HFFLOAT3 scale = { 50.f,50.f,0.f };		// サイズ
	const hft::HFFLOAT3 position = { 0.0f,0.0f,-2.0f };	// 座標
	const hft::HFFLOAT3 offset[4] = {{50.0f,0.0f,0.0f},		// 右向きのアタックマスの位置
									 {0.0f,50.0f,0.0f},		// 上向きのアタックマスの位置
									 {-50.0f,0.0f,0.0f},	// 左向きのアタックマスの位置
									 {0.0f,-50.0f,0.0f} };	// 下向きのアタックマスの位置
	const int defoult1 = 150;	// 通常状態1のフレーム
	const int defoult2 = 120;	// 通常状態2のフレーム
	const int attack = 50;	// 攻撃状態のフレーム
	const int spin = 40;	// 回転状態のフレーム
	const int dead = 50;	// 死亡状態のフレーム
	const char* BiteEnemyTexName = "Assets/01-Texture/99-Test/daruma.jpg";	// テクスチャ
}