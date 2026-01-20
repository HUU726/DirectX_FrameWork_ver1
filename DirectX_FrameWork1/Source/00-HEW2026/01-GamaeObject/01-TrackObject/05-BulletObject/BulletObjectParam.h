#pragma once

#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"

namespace BulletObjectParam
{
	BoxCollider2D* col = nullptr;	// 自身の体の判定用のコライダー
	const bool active = false;	// 弾が存在する時にtrueにし、存在しない時にfalseにする
	const int livetime = 300;	// 弾が進み続けるフレーム
	const float spead = 2.f;	// 弾の進むスピード
	const int blasttime = 30;	// 弾が炸裂してから消えるまでのフレーム
	const hft::HFFLOAT3 position = { 0.f,0.f,0.f };		// 座標
	const hft::HFFLOAT3 scale = { 20.f,20.f,-2.0f };	// サイズ

	const char* BulletObjTexName = "Assets/01-Texture/99-Test/daruma.jpg";	// テクスチャ
}