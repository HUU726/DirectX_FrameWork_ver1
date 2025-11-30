#pragma once

#include "../../06-GameObject/01-2DGameObject/GameObject2D.h"
#include "../../07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"


class TestEnemy : public GameObject2D
{
private:
	SpriteAnimator* p_spriteAnimator;

public:
	void Init() override;
	void Update() override;

};

