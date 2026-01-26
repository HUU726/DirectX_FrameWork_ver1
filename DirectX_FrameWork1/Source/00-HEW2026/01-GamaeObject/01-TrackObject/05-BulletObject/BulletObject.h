#pragma once

#include "../../../../01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"
#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include"../../../../00-HEW2026/10-Map/00-BaseMap/BaseMap.h"

// マップが5×5の時に違和感ないようにする

class BoxCollider2D;

class BulletObject : public GameObject2D
{
private:
	// 自身の体の判定用のコライダー
	BoxCollider2D* bodyColler = nullptr;

	// この弾を撃った敵の当たり判定をもらうポインタ
	Collider* _owner = nullptr;

	// マップの情報
	BaseMap* p_map = nullptr;

	// マップの端
	hft::HFFLOAT2 LeftTop;
	hft::HFFLOAT2 RightBottom;
	
	// 弾が存在する時にtrueにし、存在しない時にfalseにする
	bool active;

	// 弾が進み続けるフレーム
	int livetime;

	// 弾の進むスピード
	float spead;

	// 弾が炸裂してから消えるまでのフレーム
	int blasttime;

	// 経過時間
	int timer;

	// シーンが切り替わると一度だけ実行される
	bool startScene = true;
	
	// 弾が撃たれてから、ヒット判定に本体を含めない時間
	int NotHittime;

	enum State
	{
		defoult,
		blast,
	};
	State currentState;

	// Angleから方向の情報をDirectionへ
	int direction;	// 0:右 1:上 2:左 3:下
	
	// 方向の種類によって、自身の位置を加算する
	void UpdatePos();

	// マップの隅の超えるなら反対の座標を代入する
	void CheakMyPos();
	
public:
	BulletObject() = default;
	void Init() override {};
	void Init(/*BaseMap* p_map ,*/ BoxCollider2D* _owner, const int& NewDirection);	// マップ情報,発射元の当たり判定,方向
	void Update() override;

	void SetTag(const std::string&) { tag = "Bullet"; }
	void SetDirection(const int& NewDirection) { direction = NewDirection; }
	int GetDirection() { return direction; }
	void SetBulletActive(const bool& NewActive) { active = NewActive; }
	bool GetBulletActive() { return active; }

	
	void SetPos(const hft::HFFLOAT3& NewPosition) { p_transform->position = NewPosition; }// 座標指定
	void Defoult();
	void Blast();
	void OnCollisionEnter(Collider* _p_col) override;
};