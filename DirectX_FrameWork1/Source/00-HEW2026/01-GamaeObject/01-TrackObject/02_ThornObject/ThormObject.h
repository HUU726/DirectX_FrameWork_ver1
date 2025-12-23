#pragma once
#include "../00-TrackObject/TrackObject.h"
#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

class ThormObject : public TrackObject
{
private:
	bool isAttack = false;	//攻撃するかしないかのフラグ　trueの時は攻撃判定を出す
	int  timer = 0;			//現在の状態の経過フレームを計るタイマー
	int  attackTime = 20;	//攻撃状態のフレーム数
	int  defaultTime = 50;	//通常状態のフレーム数
	int  animationTime = 0;	//アニメーションの周期
public:
	ThormObject();
	~ThormObject();
	void Init()	  override;
	void Update() override;

	/// <summary>
	/// 一定周期でアニメーションをする
	/// </summary>
	void Animation();

	/// <summary>
	/// コライダーのアクティブ状態を変更
	/// </summary>
	/// <param name="state"></param>
	void SetColliderActive(bool state);

	/// <summary>
	/// 通常状態の処理
	/// </summary>
	void DefaultMove();

	/// <summary>
	/// 攻撃状態の処理
	/// </summary>
	void AttackMove();
};