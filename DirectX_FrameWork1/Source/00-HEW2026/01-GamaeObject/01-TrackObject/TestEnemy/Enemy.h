#pragma once

#include "../00-TrackObject/TrackObject.h"
#include "../../../../01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"

class CEnemy;

class CEnemy : public TrackObject
{
	static int s_instanceCount;		// エネミーの総数
private:
	float e_flame = 0;	// フレーム数を格納する変数
	int e_state = 0;	// 状態を表す変数
	
protected:
	void SetState(const int& NewState) { e_state = NewState; }
	int GetState() { return e_state; }
	void SetFlame(const float& NewFlame){ e_flame = NewFlame; }
	float GetFlame() { return  e_flame; }
	void AddEnemyCount() { s_instanceCount++;}
	void DeleteEnemyCount() { s_instanceCount--;}
	int GetEnemyCount() { return s_instanceCount; }
public:
	CEnemy() { AddEnemyCount(); }
	~CEnemy() { DeleteEnemyCount(); }
};