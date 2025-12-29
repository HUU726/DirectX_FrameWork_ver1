#pragma once
#include "../00-TrackObject/TrackObject.h"


//トゲオブジェクトクラス
//Thormオブジェクト側は当たり判定と影のアニメーションを行う
//トゲ本体のアニメーション用として内部にmainBodyオブジェクトを持つ

class GameObject2D;

class ThormObject : public TrackObject
{
private:
	bool isAttack;	//攻撃するかしないかのフラグ　trueの時は攻撃判定を出す
	int  timer;			//現在の状態の経過フレームを計るタイマー
	int  attackTime;	//攻撃状態のフレーム数
	int  defaultTime;	//通常状態のフレーム数
	int  animationTime;	//アニメーションの周期

	//GameObject2D mainBodyObj;	//トゲ部分のアニメーション用のオブジェクト

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
	/// 一定フレーム数経過すると攻撃状態に切り替える
	/// </summary>
	void DefaultMove();

	/// <summary>
	/// 攻撃状態の処理
	/// 一定フレーム数経過すると通常状態に切り替える
	/// </summary>
	void AttackMove();
};