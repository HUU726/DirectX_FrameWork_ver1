#pragma once
#include"../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"
#include<string>

//#include"../../../../00-HEW2026/01-GamaeObject/01-TrackObject/04_TestEnemy/BiteEnemy.h"

// 噛みつく敵本体にパラメータ
namespace BiteEnemyParam
{
	const std::string tag = "Bite";		// 本体のタグ:Bitetag
	const int anipos = 0;		// 再生するアニメーションID
	const int oldani = 0;		// 停止するアニメーションID
	const int direction = 0;	// 初期は右向き
	const int defoult1 = 100;	// 通常状態1のフレーム
	const int defoult2 = 120;	// 通常状態2のフレーム
	const int attack = 20;		// 攻撃状態のフレーム
	const int spin = 2;			// 回転状態のフレーム
	const int dead = 50;		// 死亡状態のフレーム
	const int Act[4] = { 0, 4, 0, 8 };	// 行動シーケンス
	const hft::HFFLOAT3 scale = { 150.f,150.f,1.f };	// サイズ
	const hft::HFFLOAT3 position = { 0.0f,0.0f,-2.0f };	// 座標
	const char* BiteEnemyTexName = "Assets/01-Texture/03-Enemy/EnemyKamuteki.png";	// テクスチャ
}

// 攻撃マスのパラメータ
namespace AttackMassParam
{
	const std::string tag = "Enemy";
	const bool Fg = false;
	const int direction = 0;
	const hft::HFFLOAT3 scale = { 70.f,70.f,70.f };
	const hft::HFFLOAT3 position = { 0.0f,0.0f,0.0f };
}