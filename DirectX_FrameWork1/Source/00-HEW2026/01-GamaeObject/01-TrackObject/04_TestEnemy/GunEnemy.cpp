#include"GunEnemy.h"

GunEnemy::GunEnemy()
{
	// 弾オブジェクト初期化
	// bullet = nullptr;
}

void GunEnemy::Init()
{
	// パラメータ初期化

	// 当たり判定初期化

	// アニメーション初期化
}

void GunEnemy::Update()
{
	timer++;

	switch (currentState)
	{
	case State::Defoult:
		break;
	case State::Shotting:
		break;
	case State::Dead:
		break;
	defoult:
		break;
	}
}

void GunEnemy::Defoult()
{
	// 弾がマップ上に存在しない時、待機時間を超えるとShootingへ移行
	 
	// 通常アニメーションを再生する
}

void GunEnemy::Shotting()
{
	// アニメーションを再生し、定められたフレームに弾オブジェクトを生成する

	// アニメーションの再生が終わり次第、Defoultへ移行
}

void GunEnemy::Dead()
{
	// 当たり判定の停止

	// エネミー総数の減少
	CEnemy::DownEnemyCount();
	// 死亡アニメーションを再生する

	// アニメーションが終わり次第、オブジェクトの機能を停止する
}

void OnCollisionEnter(Collider* _p_col)
{
	// 対象のオブジェクトと接触した際、Deadへ移行
}

/*
    GunEnemy();
	void Init() override;
	void Update() override;

	void Defoult();
	void Shotting();
	void Dead();

	void OnCollisionEnter(Collider* _p_col)
*/