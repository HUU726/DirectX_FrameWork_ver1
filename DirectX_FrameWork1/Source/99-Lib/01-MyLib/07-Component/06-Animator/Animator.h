#pragma once

#include "../00-Component/Component.h"
#include "../../998-FH_Types/HF_FLOAT.h"

#include <vector>
#include <memory>

//スプライトシート想定のセル構造体
struct AnimationCell
{
	float flame;			//アニメーション継続フレーム
	hft::HFFLOAT2 uv;		//UV座標
	hft::HFFLOAT2 range;	//幅
};


/******************************************************************************************/

enum class ANIM_TYPE
{
	NORMAL = 0,
	LOOP,
	BOOMERANG,
};

class Animation
{
private:
	std::vector<AnimationCell> cells;	//アニメーションセル
	int cellIndex;	//現在選択中のセル番号  ０～

	bool isActive;	//アニメーションを実行するかどうか
	ANIM_TYPE type;	//ループするかどうか
	int priority;	//アニメーション優先順位

public:
	Animation();
	/*** ゲッター ***/
	bool GetActive() const { return isActive; }
	int GetPriority() const { return priority; }
	ANIM_TYPE GetType() const { return type; }

	/*** セッター ***/
	void Active() { isActive = true; }
	void InActive() { isActive = false; }
	void SetPriority(int _priority) { priority = _priority; }
	void AddCell(const AnimationCell& _cell);
	void AddCells(const std::vector<AnimationCell> _cells);
	void SetType(ANIM_TYPE _type) { type = _type; }

	void SendTex();

	void Update();

};

/******************************************************************************************/

class Animator : public Component
{
private:
	std::vector<Animation> animations;	//アニメーション(優先度の高いアニメーションほど若い添え字)
	int animIndex;	//現在アクティブなアニメーション


public:
	/*** セッター ***/
	void AddAnimation(const Animation& _anim);

	void SendTex();

	void Init() override;
	void Update() override;

};

