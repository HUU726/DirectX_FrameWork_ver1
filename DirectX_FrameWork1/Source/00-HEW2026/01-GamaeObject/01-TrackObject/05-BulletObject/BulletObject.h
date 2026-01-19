#pragma once

#include "../../../../01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"
#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

class BoxCollider2D;

class BulletObject : public GameObject2D
{
private:
	// 自身の体の判定用のコライダー
	BoxCollider2D* bodyColler = nullptr;

	// マップの端
	hft::HFFLOAT2 LeftTop;
	hft::HFFLOAT2 RightBottom;

	// 弾が存在する時にtrueにし、存在しない時にfalseにする
	bool active = false;

	// 弾が進み続けるフレーム
	int livetime = 300;

	// 弾の進むスピード
	float spead = 2.f;

	// 弾が炸裂してから消えるまでのフレーム
	int blasttime = 30;

	// 経過時間
	int timer = 0;

	// 方向
	hft::HFFLOAT2 Iangle;

	enum State
	{
		defoult,
		blast,
	};
	State currentState;

	// Angleから方向の情報をDirectionへ
	int direction;	// 0:右 1:上 2:左 3:下
	void SetDirection(const int& NewDirection) { direction = NewDirection; }
	int GetDirection() { return direction; }

	// 方向の種類によって、自身の位置を加算する
	void UpdatePos();

	// マップの隅の超えるなら反対の座標を代入する
	void CheakMyPos();

public:
	BulletObject();
	void Init() override;
	void Init(const hft::HFFLOAT2& NewAngle);	// 方向指定
	void Update() override;

	void SetPos(const hft::HFFLOAT3& NewPosition) { p_transform->position = NewPosition; }// 座標指定

	void SetBulletActive(const bool& NewActive) { active = NewActive; }
	bool GetBulletActive() { return active; }

	void Defoult();
	void Blast();

	void OnCollisionEnter(Collider* _p_col) override;
};