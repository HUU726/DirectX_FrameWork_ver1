#pragma once

#include "../../06-GameObject/01-2DGameObject/GameObject2D.h"
#include "../../07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"


class CEnemy : public GameObject2D
{
private:
	float e_flame = 0;	// ƒtƒŒ[ƒ€”‚ğŠi”[‚·‚é•Ï”
	int e_state = 0;	// ó‘Ô‚ğ•\‚·•Ï”
protected:
	void SetState(const int&);
	int GetState();
	void SetFlame(const float&);
	float GetFlame();
};