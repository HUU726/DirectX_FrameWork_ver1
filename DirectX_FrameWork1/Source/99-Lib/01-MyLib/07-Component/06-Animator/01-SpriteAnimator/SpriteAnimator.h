#pragma once

#include "../../00-Component/Component.h"
#include "../../../998-FH_Types/HF_FLOAT.h"

#include <vector>
#include <memory>

//スプライトシート想定のセル構造体
struct SpriteAnimationCell
{
	float flame;			//アニメーション継続フレーム
	hft::HFFLOAT2 uv;		//UV座標
};


/******************************************************************************************/

enum class SPRITE_ANIM_TYPE
{
	NORMAL = 0,
	LOOP,
	BOOMERANG,
};

class SpriteAnimation
{
private:
	std::vector<SpriteAnimationCell> cells;	//アニメーションセル
	int cellIndex;	//現在選択中のセル番号  ０～
	int curFlame;
	int moveVec;

	bool isActive;	//アニメーションを実行するかどうか
	SPRITE_ANIM_TYPE type;	//ループするかどうか
	int priority;	//アニメーション優先順位

public:
	SpriteAnimation();
	SpriteAnimation(hft::HFFLOAT2 _spriteDiv, hft::HFFLOAT2 _startIndex, float _cellNum);
	/*** ゲッター ***/
	bool GetActive() const { return isActive; }
	int GetPriority() const { return priority; }
	SpriteAnimationCell& GetCell(int _index) { return cells.at(_index); }
	SPRITE_ANIM_TYPE GetType() const { return type; }

	/*** セッター ***/
	void Active() { isActive = true; }
	void InActive() { isActive = false; }
	void SetPriority(int _priority) { priority = _priority; }
	void AddCell(const SpriteAnimationCell& _cell);
	void AddCells(const std::vector<SpriteAnimationCell>& _cells);
	void SetType(SPRITE_ANIM_TYPE _type) { type = _type; }

	void SendTex();

	void Update();

};

/******************************************************************************************/

class SpriteAnimator : public Component
{
private:
	std::vector<SpriteAnimation> animations;	//アニメーション(優先度の高いアニメーションほど若い添え字)
	int animIndex;	//現在アクティブなアニメーション
	hft::HFFLOAT2 division;


public:
	SpriteAnimator();
	SpriteAnimator(hft::HFFLOAT2 _div);
	/*** セッター ***/
	void AddAnimation(const SpriteAnimation& _anim);
	void SetDivisions(hft::HFFLOAT2 _div);

	void SendTex();

	void Init() override;
	void Update() override;

};

