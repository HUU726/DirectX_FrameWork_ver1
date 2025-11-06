#include "Animator.h"


#include "../../02-Renderer/01-Sprite2DRenderer/Sprite2DRenderer.h"


Animation::Animation()
{
	cellIndex = 0;
	curFlame = 0;
	moveVec = 1;
	isActive = false;
	priority = 0;
	type = ANIM_TYPE::NORMAL;
}

void Animation::AddCell(const AnimationCell& _cell)
{
	cells.push_back(AnimationCell(_cell));
}

void Animation::AddCells(const std::vector<AnimationCell>& _cells)
{
	cells = _cells;
}

void Animation::SendTex()
{
	hft::HFFLOAT2 l_uv = cells.at(cellIndex).uv;
	Sprite2DRenderer::GetInstance().SetTex(l_uv);
}

void Animation::Update()
{

	hft::HFFLOAT2 l_uv = cells.at(cellIndex).uv;
	Sprite2DRenderer::GetInstance().SetTex(l_uv);


	curFlame++;

	if (cells.at(cellIndex).flame <= curFlame)
	{
		curFlame = 0;
		cellIndex += moveVec;
	}
	if (cellIndex >= cells.size() || cellIndex < 0)
	{
		switch (type)
		{
		case ANIM_TYPE::NORMAL:
			cellIndex = 0;
			isActive = false;
			break;
		case ANIM_TYPE::LOOP:
			cellIndex = 0;
			break;
		case ANIM_TYPE::BOOMERANG:
			moveVec *= -1;
			cellIndex += moveVec;
			break;
		default: break;
		}
	}

}

/******************************************************************************************/
//—Dæ“x‚Ì‚‚¢‡‚É“ü‚ê‚Ä‚¢‚­
void Animator::AddAnimation(const Animation& _anim)
{
	int index = 0;
	for ( int i = 0; i < animations.size(); i++)
	{
		if (animations[i].GetPriority() < _anim.GetPriority())
			index = i;
	}

	animations.insert(animations.begin() + index, Animation(_anim));
}


void Animator::SendTex()
{
	animations.at(animIndex).SendTex();
}

void Animator::Init()
{
}

void Animator::Update()
{

	for (auto& anim : animations)
	{
		if (anim.GetActive())
		{
			anim.Update();
			break;
		}
	}
}
