#pragma once

#include "../00-TrackObject/TrackObject.h"

#include <vector>

// 前方宣言
class BaseMap;
class Input;
class TuningFork;
class Arrow;

enum class PLAYER_STATE {
    STAND, SELECT, CHARGE, RELEASE, HIT, DEAD
};

class PlayerObject : public TrackObject
{
private:
    // オブジェクトTAG = Player //

    // 攻撃アニメーションのタイミング定数
    const int SLIDE_START_TIMING = 9;
    const int SLIDE_END_TIMING = 30;

    BaseMap* pMap = nullptr;
    Input* pInput = nullptr;

    /* ゲームに合わせて変更して良い変数 */
    int hitpoint = 3;
    int max_hitpoint = 3;
    float hammer_power = 0.0f;
	const float max_hammer_power = 8.0f; // 最大まで引っ張った時のパワー //memo:１以外の奇数の時+1、以降も継続（7.f = 10マスズラす）
    const float limit_hammer_power = 5.f; // 引っ張りで溜められる限界パワー
	const float charge_speed = 0.2f; // チャージ速度
    //////////////////////////////////////

    int chargeTimer = 0;
	int chargeflame = 4; // チャージアニメーションのフレーム数
    bool isChargeLoop = false;

    bool invincible = false;
    float inv_time = 2.0f;
	float inv_cnt = 0.0f;

    bool isDead = false;
    const int DEAD_ANIM_END = 42;

    // チャージ中に決定した攻撃方向を保存しておく変数
    hft::HFFLOAT2 attackDirection = { 0, 0 };

	bool controllerMode = false;        // コントローラーで操作中かどうか
	bool mouseMode = false;           // マウスで操作中かどうか

    int SE_LAttack = -1;
	int SE_MAttack = -1;
    int SE_SAttack = -1;
    int SE_Charge = -1;
    int SE_Hit = -1;
    int SE_Dead = -1;

    hft::HFFLOAT2 dragStartPos = { 0, 0 }; // ドラッグ開始位置

    PLAYER_STATE state;
    int animTimer;

    TuningFork* pTuningFork = nullptr;
    Arrow* pArrow = nullptr;

    float tileSize = 100.0f;

    //削除待ちの音叉を一時保管するリスト（static）
    static std::vector<TuningFork*> garbageForks;
    static std::vector<Arrow*> garbageArrows;

    void UpdateStand();
    void UpdateSelect();
    void UpdateCharge();
    void UpdateRelease();
    void UpdateDamage();
    void UpdateDead();

    void OnHit();
    void OnDead();

    hft::HFFLOAT2 GetTargetIndex() const;
    hft::HFFLOAT2 GetVecFromAngle(float _angle) const;
    float GetAngleFromVec(hft::HFFLOAT2 _vec) const;
    void ChangeState(PLAYER_STATE _nextState);

public:
    PlayerObject();
    ~PlayerObject();

    void Init() override {}
    void Init(BaseMap* _pMap, Input* _pInput);
    void Update() override;
    void OnCollisionEnter(Collider* _p_col) override;

    // ゲッター //
    PLAYER_STATE GetPlayerState() { return state; }

    int GetPlayerHP() { return hitpoint; }
	int GetPlayerMaxHP() { return max_hitpoint; }

	bool GetIsInvincible() { return invincible; } // 無敵状態かどうか
	bool GetIsDead() { return isDead; }           // 死亡状態かどうか

	float GetHammerPower() { return hammer_power; }             //現在のハンマーパワー
	float GetMaxHammerPower() { return max_hammer_power; }      //ハンマーパワーの最大値
	float GetLimitHammerPower() { return limit_hammer_power; }  //引っ張りで溜められる最大パワー
};