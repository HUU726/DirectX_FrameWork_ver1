#pragma once

#include "../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"

namespace GunEnemyParam
{
	const std::string tag = "Gun";	// タグ:"Gun"
	const int waittimer = 180;	// 弾が消えてからの待機時間
	const int bulletcreateflame = 50;		// シューティングのフレーム数
	const bool changeScene = false;			// シーンが切り替わった時に一度だけ再生されるようにする
	const bool startScene = true;			// 一度だけ再生される
	const int anipos = 0;					// 新しいアニメーションを再生するためのID格納用変数
	const int oldani = 0;					// 古いアニメーションをストップさせるためのID格納用変数
	const hft::HFFLOAT3 scale = { 130.f,130.f, 50.f };		// サイズ
	const hft::HFFLOAT3 position = { 0.0f,0.0f, -2.0f };	// 位置
	const char* biteenemyTexName = "Assets/01-Texture/03-Enemy/EnemyTamateki.png";	// テクスチャ
}