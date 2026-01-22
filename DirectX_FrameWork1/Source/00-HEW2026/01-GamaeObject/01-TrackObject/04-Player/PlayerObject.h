#pragma once

#include "../00-TrackObject/TrackObject.h"

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
    const int SLIDE_START_TIMING = 8;
    const int SLIDE_END_TIMING = 20;

    BaseMap* pMap = nullptr;
    Input* pInput = nullptr;

    int hitpoint = 3;
    int max_hitpoint = 3;
    float hammer_power = 0.0f;
    const float max_hammer_power = 30.0f; //めちゃつよなので後から変えてもよし
    bool invincible = false;
    float inv_time = 1.0f;

    PLAYER_STATE state;
    int animTimer;

    TuningFork* pTuningFork = nullptr;
    Arrow* pArrow = nullptr;

    void UpdateStand();
    void UpdateSelect();
    void UpdateCharge();
    void UpdateRelease();
    void UpdateDamage();

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

    //ゲッター
    PLAYER_STATE GetPlayerState() { return state; }
    int GetPlayerHP() { return hitpoint; }
};