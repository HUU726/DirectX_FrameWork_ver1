#include "SpriteAnimator.h"


#include "../../../02-Renderer/01-Sprite2DRenderer/Sprite2DRenderer.h"
#include "../../../06-GameObject/GameObject.h"
#include "../../02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../../02-Renderer/99-ShapeTable/01-ShapeTable2D/ShapeTable2D.h"


SpriteAnimation::SpriteAnimation()
{
	cellIndex = 0;
	curFlame = 0;
	moveVec = 1;
	isActive = false;
	priority = 0;
	type = SPRITE_ANIM_TYPE::NORMAL;
}

SpriteAnimation::SpriteAnimation(hft::HFFLOAT2 _spriteDiv, hft::HFFLOAT2 _startIndex, float _cellNum)
{

	cellIndex = 0;
	curFlame = 0;
	moveVec = 1;
	isActive = false;
	priority = 0;
	type = SPRITE_ANIM_TYPE::NORMAL;

	float cellNum = _spriteDiv.x * _spriteDiv.y;
	hft::HFFLOAT2 cellScl;
	cellScl.x = 1.0f / _spriteDiv.x;
	cellScl.y = 1.0f / _spriteDiv.y;

	float curX = _startIndex.x;
	float curY = _startIndex.y;

	for (int i = 0; i < _cellNum; i++)
	{
		SpriteAnimationCell cell;
		cell.uv.x = cellScl.x * curX;
		cell.uv.y = cellScl.y * curY;
		cells.push_back(cell);

		curX++;
		if (curX >= _spriteDiv.x)
		{
			curX = 0;
			curY++;
		}
	}
}


void SpriteAnimation::AddCell(const SpriteAnimationCell& _cell)
{
	cells.push_back(SpriteAnimationCell(_cell));
}

void SpriteAnimation::AddCells(const std::vector<SpriteAnimationCell>& _cells)
{
	cells = _cells;
}

void SpriteAnimation::SendTex()
{
	hft::HFFLOAT2 l_uv = cells.at(cellIndex).uv;
	Sprite2DRenderer::GetInstance().SetTex(l_uv);
}

void SpriteAnimation::Update()
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
		case SPRITE_ANIM_TYPE::NORMAL:
			cellIndex = 0;
			isActive = false;
			break;
		case SPRITE_ANIM_TYPE::LOOP:
			cellIndex = 0;
			break;
		case SPRITE_ANIM_TYPE::BOOMERANG:
			moveVec *= -1;
			cellIndex += moveVec * 2;
			break;
		default: break;
		}
	}

}

/******************************************************************************************/
SpriteAnimator::SpriteAnimator()
{
	animIndex = 0;
	division = { 1,1 };
}

SpriteAnimator::SpriteAnimator(hft::HFFLOAT2 _div)
{
	animIndex = 0;
	division = _div;
}

//—Dæ“x‚Ì‚‚¢‡‚É“ü‚ê‚Ä‚¢‚­
void SpriteAnimator::AddAnimation(const SpriteAnimation& _anim)
{
	int index = 0;
	for ( int i = 0; i < animations.size(); i++)
	{
		if (animations[i].GetPriority() < _anim.GetPriority())
			index = i;
	}

	animations.insert(animations.begin() + index, SpriteAnimation(_anim));
}

void SpriteAnimator::SetDivisions(hft::HFFLOAT2 _div)
{
	division = _div;
	if (auto comp = gameObject->GetComponent<SpriteRenderer>())
	{
		hft::HFFLOAT2 cellScl;
		cellScl.x = 1.0 / division.x;
		cellScl.y = 1.0 / division.y;
		auto polygon = ShapeTable2D::GetInstance().GetShape("sprite");
		polygon->vertices[1].uv = { cellScl.x,0 };
		polygon->vertices[2].uv = { 0,cellScl.y };
		polygon->vertices[3].uv = { cellScl.x,cellScl.y };
		hft::CreateVertexBuffer(polygon);
		polygon->p_indexBuffer = ShapeTable2D::GetInstance().GetIndexBuffer("sprite");
		comp->SetShape(polygon);
	}
}


void SpriteAnimator::SendTex()
{
	animations.at(animIndex).SendTex();
}

void SpriteAnimator::Play(int _id)
{
	SpriteAnimation& useAnim = animations.at(0);
	for (auto& anim : animations)
	{
		if (anim.GetID() == _id)
		{
			useAnim = anim;
			break;
		}
	}
	useAnim.Active();
}

void SpriteAnimator::Stop(int _id)
{
	SpriteAnimation& useAnim = animations.at(0);
	for (auto& anim : animations)
	{
		if (anim.GetID() == _id)
		{
			useAnim = anim;
			break;
		}
	}
	useAnim.InActive();
}

void SpriteAnimator::Init()
{
	if (!(division == hft::HFFLOAT2(1, 1)))
		SetDivisions(division);
}

void SpriteAnimator::Update()
{
	for (animIndex = 0; animIndex < animations.size(); animIndex++)
	{
		if (animations.at(animIndex).GetActive())
		{
			animations.at(animIndex).Update();
			return;
		}
	}

	animIndex = 0;
}
