#pragma once

#include "../00-TrackObject/TrackObject.h"
#include "../../../../01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"

class CEnemy;

class CEnemy : public TrackObject
{
	inline static int s_instanceCount = 0;		// エネミーの総数
private:
	int fg;	// 0:死亡フラグON 1:死亡フラグOFF	  
public:
	CEnemy() { s_instanceCount++; fg = 0; }	// エネミーの総数追加

	// エネミーの死亡フラグがOFFになった時、一回だけ実行される(エネミーの総数の減少)
	void DownEnemyCount() { if (fg == 0) { s_instanceCount--; fg++;} }
	 
	// エネミー総数を返す
	int GetEnemyCount() { return s_instanceCount; }		
};