#pragma once
#include<string>
#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"

namespace BulletObjectParam
{
	const std::string tag = "DamageObject";	// タグ
	const bool active = false;				// 弾が存在する時にtrueにし、存在しない時にfalseにする
	const int livetime = 300;				// 弾が進み続けるフレーム
	const float spead = 3.f;				// 弾の進むスピード
	const bool startTrigger = true;			// アクティブになると一度だけ実行される
	const hft::HFFLOAT3 position = { 1000.f,1000.f,-2.f };			// 座標
	const hft::HFFLOAT3 scale = { 30.f,30.f,1.0f };					// サイズ
	const char* BulletObjTexName = "Assets/01-Texture/03-Enemy/Bullet.png";	// テクスチャ
}