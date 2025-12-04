#pragma once

#include "../../../998-FH_Types/HF_FLOAT.h"

#include <vector>
#include <memory>

//スプライトシート想定のセル構造体
struct SpriteAnimationCell
{
	float flame;		//アニメーション継続フレーム
	hft::HFFLOAT2 uv;	//UV座標
};


/******************************************************************************************/


enum class SPRITE_ANIM_TYPE
{
	NORMAL = 0,	//ループなし	0～N
	LOOP,		//ループ		0～N → 0～N → N～0 → ・・・
	BOOMERANG,	//ブーメラン	0～N → N～0 → 0～N → ・・・
};

class SpriteAnimation
{
private:
	int id;	//アニメーションID(各アニメーターごとに連番)
	std::vector<SpriteAnimationCell> cells;	//アニメーションセル
	int cellIndex;	//現在選択中のセル番号  0～N
	int curFlame;	//現在セルの経過フレーム
	int moveVec;	//cellIndexの移動方向	1：0→N		2：N → 0

	bool isActive;			//アニメーションを実行するかどうか
	SPRITE_ANIM_TYPE type;	//アニメーションの挙動	Normal/Loop/Boomerang
	int priority;			//アニメーション優先順位	数字が大きい ＝ 優先度が高い

public:
	SpriteAnimation();
	SpriteAnimation(hft::HFFLOAT2 _spriteDiv, hft::HFFLOAT2 _startIndex, float _cellNum);
	/*** ゲッター ***/
	int GetID() const { return id; }
	SPRITE_ANIM_TYPE GetType() const { return type; }
	bool GetActive() const { return isActive; }
	int GetPriority() const { return priority; }
	/**
	* @brief	特定セルの参照を取得
	* @param	int		_index	セル番号
	* @return	SpriteAnimationCell&	参照アニメーションセル
	*/
	SpriteAnimationCell& GetCellRef(int _index) { return cells.at(_index); }

	/*** セッター ***/
	void Active();
	void InActive();
	void SetID(int _id) { id = _id; }
	void SetPriority(int _priority) { priority = _priority; }
	void SetType(SPRITE_ANIM_TYPE _type) { type = _type; }
	void AddCell(const SpriteAnimationCell& _cell);
	void AddCells(const std::vector<SpriteAnimationCell>& _cells);

	/**
	* @brief	現在のUVをRendererに送信
	*/
	void SendTex();

	void Update();

};

/******************************************************************************************/
#include "../../00-Component/Component.h"


class SpriteAnimator : public Component
{
private:
	std::vector<SpriteAnimation> animations;	//アニメーション(優先度の高いアニメーションほど若い添え字)
	int animIndex;			//現在アクティブなアニメーションの総番号
	hft::HFFLOAT2 division;	//スプライトシート分割数

public:
	SpriteAnimator();
	SpriteAnimator(hft::HFFLOAT2 _div);
	~SpriteAnimator();
	/*** セッター ***/
	void AddAnimation(const SpriteAnimation& _anim);
	void SetDivisions(hft::HFFLOAT2 _div);

	/*** ゲッター ***/
	hft::HFFLOAT2 GetDivision() const { return division; }

	/**
	* @brief	現在のUVをRendererに送る
	*/
	void SendTex();
	/**
	* @brief	アニメーションを有効にする
	* @param	int		_id		アニメーション番号
	*/
	void Play(int _id);
	/**
	* @brief	アニメーションを無効にする
	* @param	int		_id		アニメーション番号
	*/
	void Stop(int _id);

	void Init() override;
	void Update() override;

	void Action();

};

