#pragma once

#include "../00-TrackObject/TrackObject.h"
#include "../../../../01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"


class CEnemy : public TrackObject
{
private:
	float e_flame = 0;	// フレーム数を格納する変数
	int e_state = 0;	// 状態を表す変数
	static int* cnt;		// エネミーの総数
protected:
	void SetState(const int& NewState) { e_state = NewState; }
	int GetState() { return e_state; }
	void SetFlame(const float& NewFlame){ e_flame = NewFlame; }
	float GetFlame() { return  e_flame; }
	void AddEnemyCount() { cnt++;}
	void DeleteEnemyCount() { cnt--;}
	int GetEnemyCount() { return *cnt; }
};