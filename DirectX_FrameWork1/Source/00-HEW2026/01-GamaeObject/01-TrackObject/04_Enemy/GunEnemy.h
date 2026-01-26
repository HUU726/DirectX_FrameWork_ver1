#pragma once
#include "Enemy.h"
#include"../05-BulletObject/BulletObject.h"
#include"../../../../01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include"../../../../00-HEW2026/10-Map/00-BaseMap/BaseMap.h"

class GunEnemy : public CEnemy
{
private:
	// 自身の体の判定用のコライダー
	BoxCollider2D* bodyColl = nullptr;
	// マップの情報
	BaseMap* p_map = nullptr;
	// 弾が消えてからの待機時間
	int waittimer;
	// 経過時間
	int timer;
	// 方向
	int direction;
	// シーンが切り替わった時に一度だけ再生されるようにする
	bool changeScene;
	// 一度だけ再生されるようにする
	bool startScene;
	// 新しいアニメーションを再生するためのID格納用変数
	int anipos;
	// 古いアニメーションをストップさせるためのID格納用変数
	int oldani;
	// 弾オブジェクトを作成するフレーム数
	int bulletcreateflame;
	
	enum State
	{
		defoult,
		shotting,
		dead
	};
	State currentState;
	
	void SetDirection(const int& NewDirection) { direction = NewDirection; }
	int GetDirection() { return direction; }

	
	// 弾オブジェクト
	BulletObject bullet;

public:
	GunEnemy();
	void Init() override {};
	void Init(BaseMap* p_map, const int& NewDirection);
	void Update() override;
	
	void Defoult();
	void Shotting();
	void Dead();
	
	void OnCollisionEnter(Collider* _p_col) override;
};

/*
class ObjectManager
{
public:
	template<class T, class... Args>
	static T* Create(Args&&... args)
	{
		T* obj = new T(std::forward<Args>(args)...);
		obj->InternalInitialize(); // Transform / Component 初期化
		objects.push_back(obj);
		return obj;
	}

private:
	static inline std::vector<GameObject*> objects;
};
*/