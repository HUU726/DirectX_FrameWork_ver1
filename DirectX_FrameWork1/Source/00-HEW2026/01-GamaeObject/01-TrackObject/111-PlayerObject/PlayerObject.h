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
    // 攻撃アニメーションのタイミング定数
    const int SLIDE_TIMING = 8;
    const int ANIM_END_TIME = 20;

    BaseMap* pMap = nullptr;
    Input* pInput = nullptr;

    int hitpoint;
    float hammer_power;
    const float max_hammer_power = 30.0f;
    bool invincible;
    float inv_time;

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

    void Init(BaseMap* _pMap, Input* _pInput);
    void Update() override;
    void OnCollisionEnter2D(Collider2D* _p_col) override;

    //ゲッター
    PLAYER_STATE GetPlayerState() { return state; }
    int GetPlayerHP() { return hitpoint; }
};