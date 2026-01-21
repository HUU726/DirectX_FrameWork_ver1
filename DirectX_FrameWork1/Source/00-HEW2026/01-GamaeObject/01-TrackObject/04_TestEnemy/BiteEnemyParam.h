#pragma once
#include"../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"
#include<string>

//#include"../../../../00-HEW2026/01-GamaeObject/01-TrackObject/04_TestEnemy/BiteEnemy.h"

namespace BiteEnemyParam
{
	const std::string tag = "Bite";		// 本体のタグ:Bitetag
	const std::string attacktag = "Enemy";		// 攻撃マスのタグ:Enemy
	const int hitstoptime = 10;	// ヒットストップ時間
	const int direction = 0;	// 初期は右向き
	const int anipos = 0;		// 再生するアニメーションID
	const int oldani = 0;		// ストップするアニメーションID
	const int Act[4] = { 0, 4, 0, 8 };	// 行動シーケンス
	const hft::HFFLOAT3 scale = { 100.f,100.f,0.f };		// サイズ
	const hft::HFFLOAT3 position = { 0.0f,0.0f,-2.0f };	// 座標
	const hft::HFFLOAT3 offset[4] = {};		// 0:// 右向きのアタックマスの位置 1:// 上向きのアタックマスの位置 2:// 左向きのアタックマスの位置	3:// 下向きのアタックマスの位置
	const int defoult1 = 100;	// 通常状態1のフレーム
	const int defoult2 = 120;	// 通常状態2のフレーム
	const int attack = 20;	// 攻撃状態のフレーム
	const int spin = 2;	// 回転状態のフレーム
	const int dead = 50;	// 死亡状態のフレーム
	const char* BiteEnemyTexName = "Assets/01-Texture/03-Enemy/EnemyKamuteki.png";	// テクスチャ
}