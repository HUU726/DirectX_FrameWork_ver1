#pragma once

#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"

namespace BulletObjectParam
{
	BoxCollider2D* col = nullptr;	// 自身の体の判定用のコライダー
	const std::string tag = "Bullet";	// タグ
	const bool active = false;	// 弾が存在する時にtrueにし、存在しない時にfalseにする
	const int livetime = 300;	// 弾が進み続けるフレーム
	const float spead = 2.f;	// 弾の進むスピード
	const int blasttime = 30;	// 弾が炸裂してから消えるまでのフレーム
	const bool startScene = true;	// シーンが切り替わると一度だけ実行される
	const bool OneHit = true;		// 弾を撃つ際に当たり判定を肩代わり
	const int NotHittime = 10;		// 弾が撃たれてから、ヒット判定に本体を含めない時間
	const hft::HFFLOAT3 position = { 0.f,0.f,-2.f };		// 座標
	const hft::HFFLOAT3 scale = { 50.f,50.f,1.0f };			// サイズ

	const char* BulletObjTexName = "Assets/01-Texture/03-Enemy/Bullet.png";	// テクスチャ
}