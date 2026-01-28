#pragma once
#include "../00-TrackObject/TrackObject.h"

#include "../../../../99-Lib/01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"

//朝日奈担当トゲオブジェクトクラス
//Thormオブジェクト側は当たり判定と影のアニメーションを行う
//トゲ本体のアニメーション用として内部にmainBodyオブジェクトを持つ


class ThormObject : public TrackObject
{
private:
	enum State {
		Default,
		Falling,
		Attack
	};

	State currentState; //現在の状態を識別する
	int  timer;			//経過フレームを計るタイマー

	int  attackTime;	//攻撃状態のフレーム数
	int  fallTime;		//落下状態のフレーム数
	int  defaultTime;	//通常状態のフレーム数
	

	//トゲ用のパラメータ
	float thormFallSpeed;				//トゲの落下速度
	float distanceHold; //トゲと影の距離のしきい値
	float scaleDownSpeed;
	int thormFallWaitTime;	//トゲが再度落下するまでの待ち時間
	int thormFallAcceleration;//トゲの落下加速度
	hft::HFFLOAT3 initialOffset; //トゲと影の距離の初期値
	hft::HFFLOAT3 initialScale;  //トゲの画像の初期サイズ

	GameObject2D mainBodyObj;	//トゲ部分のアニメーション用のオブジェクト
public:
	ThormObject();
	~ThormObject();
	void Init()	  override;
	void Update() override;

	/// <summary>
	/// 影の部分の更新処理
	/// 状態の切り替え、コライダーのアクティブ状態切り替えを行う
	/// </summary>
	void ShadowUpdate();

	/// <summary>
	/// 通常状態の処理
	/// 一定フレーム数経過すると落下状態に切り替える
	/// </summary>
	void DefaultMove();

	/// <summary>
	/// 落下状態の処理
	/// 一定フレーム数経過すると攻撃状態に切り替える
	/// </summary>
	void FallingMove();

	/// <summary>
	/// 攻撃状態の処理
	/// 一定フレーム数経過すると通常状態に切り替える
	/// </summary>
	void AttackMove();


	/// <summary>
	/// コライダーのアクティブ状態を変更
	/// </summary>
	/// <param name="state"></param>
	void SetColliderActive(bool state);


	/// <summary>
	/// トゲの落下アニメーション
	/// </summary>
	void ThormAnimation(const State state);
};