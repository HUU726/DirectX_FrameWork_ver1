#include "Animator.h"


#include "../../02-Renderer/01-Sprite2DRenderer/Sprite2DRenderer.h"


void Animation::AddCell(const AnimationCell& _cell)
{
	cells.push_back(AnimationCell(_cell));
}

void Animation::SendTex()
{
	hft::HFFLOAT2 l_uv = cells.at(cellIndex).uv;
	Sprite2DRenderer::GetInstance().SetTex(l_uv);
}

void Animation::Update()
{
	static float nowFlame = 0;

	hft::HFFLOAT2 l_uv = cells.at(cellIndex).uv;
	Sprite2DRenderer::GetInstance().SetTex(l_uv);


	nowFlame++;

	if (cells.at(cellIndex).flame <= nowFlame)
	{
		nowFlame = 0;
		cellIndex++;
	}
	if (cellIndex > cells.size())
		cellIndex = 0;

}

/******************************************************************************************/
//óDêÊìxÇÃçÇÇ¢èáÇ…ì¸ÇÍÇƒÇ¢Ç≠
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
