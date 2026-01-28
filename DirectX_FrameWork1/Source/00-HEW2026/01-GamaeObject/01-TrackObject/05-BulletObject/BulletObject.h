#pragma once

#include "../../../../01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"
#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include"../../../../00-HEW2026/10-Map/00-BaseMap/BaseMap.h"

// マップが5×5の時に違和感ないようにする

class BoxCollider2D;

class BulletObject : public GameObject2D
{
private:
	hft::HFFLOAT2 LeftTop;			// マップの端(左、上)
	hft::HFFLOAT2 RightBottom;		// マップの端(右、下)
	bool active;					// 弾が存在する時にtrueにし、存在しない時にfalseにする
	int livetime;					// 弾が進み続けるフレーム
	float spead;					// 弾の進むスピード
	int blasttime;					// 弾が炸裂してから消えるまでのフレーム
	int timer;						// 経過時間
	bool startScene;				// シーンが切り替わると一度だけ実行される
	int NotHittime;					// 弾が撃たれてから、ヒット判定に本体を含めない時間
	int direction;					// 方向の情報を値として格納する変数(0:右 1:上 2:左 3:下)

	enum State
	{
		defoult,
		blast,
	};
	State currentState;
	
	void UpdatePos();				// 方向の種類によって、自身の位置を加算する
	void CheakMyPos();				// マップの隅の超えるなら反対の座標を代入する

	BoxCollider2D* bodyCollider;	// 自身の体の判定用のコライダー
	BaseMap* p_map;					// マップの情報
public:
	void Init() override {};
	void Init(BaseMap* p_map,const int& NewDirection);	// マップ情報,発射元の当たり判定,方向
	void Update() override;

	void SetTag(const std::string& NewTag) { tag = NewTag; }
	void SetDirection(const int& NewDirection) { direction = NewDirection; }
	int GetDirection() { return direction; }
	void SetBulletActive(const bool& NewActive) { active = NewActive; }
	bool GetBulletActive() { return active; }

	
	void SetPos(const hft::HFFLOAT3& NewPosition) { p_transform->position = NewPosition; }	// 座標指定
	
	void Defoult();
	void Blast();
	void OnCollisionEnter(Collider* _p_col) override;
};