#pragma once
#include "Enemy.h"
#include"../05-BulletObject/BulletObject.h"
#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include"../../../../00-HEW2026/10-Map/00-BaseMap/BaseMap.h"

class GunEnemy : public CEnemy
{
private:
	int timer;							// 経過時間
	int direction;						// 方向
	int waittimer;						// 弾が消えてからの待機時間
	int anipos;							// 新しいアニメーションを再生するためのID格納用変数
	int oldani;							// 古いアニメーションをストップさせるためのID格納用変数
	int bulletcreateflame;				// 弾オブジェクトを作成するフレーム数
	int deadtime;						// 死亡状態が終了する時間
	bool startTrigger;					// 一度だけ再生されるようにする
	bool changeTrigger;					// シーンが切り替わった時に一度だけ再生されるようにする

	enum State
	{
		defoult,
		shotting,
		dead
	};
	State currentState;
	
	void Defoult();
	void Shotting();
	void Dead();

	void SetDirection(const int& NewDirection) { direction = NewDirection; }
	int GetDirection() { return direction; }
	
	static std::vector<BulletObject*> ptr_num;	// 削除する予定のオブジェクトを一時保
	BulletObject* bullet;						// 弾オブジェクト

	int SE_Shot = -1;							// 効果音(ショット)
	int SE_Reload = -1;							// 効果音(リロード)
	int SE_Dead = -1;							// 効果音(死亡)
public:
	GunEnemy();
	~GunEnemy();
	void Init() override {};
	void Init(BaseMap* p_map,const int& NewDirection);
	void Update() override;

	void OnCollisionEnter(Collider* _p_col) override;
};