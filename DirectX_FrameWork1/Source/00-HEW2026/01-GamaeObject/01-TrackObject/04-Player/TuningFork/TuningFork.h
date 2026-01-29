#pragma once
#include "../../../../../99-Lib/01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"
#include "../../00-TrackObject/TrackObject.h"
#include "EffectFork.h"

// アニメーションの状態
enum class FORK_ANIM_STATE {
    NONE,       // 通常（非表示 または プレビュー中）
    APPEAR,     // スッと降りてくる
    IDLE,       // 設置完了（チャージ中）
    DISAPPEAR   // スッと消える
};

class TuningFork : public TrackObject
{
private:
    std::vector<EffectFork*> effects;

    float scaleRatio = 1.0f;

    // アニメーション制御用
    FORK_ANIM_STATE animState = FORK_ANIM_STATE::NONE;
    int animTimer = 0;
    const int ANIM_DURATION = 12; // 12フレーム（約0.2秒）で設置
    hft::HFFLOAT2 targetPos = { 0,0 }; // 設置目標地点

    void UpdateEffects();

public:
    TuningFork();
    ~TuningFork();

    void Init() override;
    void Init(float _scaleRatio);
    void Update() override;

    void ShowAt(const hft::HFFLOAT2& _index);
    void Hide();

    void PlayHitEffect();

    void SetAlpha(float a);

    // 演出開始メソッド
    void PlayAppear(const hft::HFFLOAT2& _pos); // 出現（設置）
    void PlayDisappear();                       // 消失（キャンセル）

    // アニメーション中かどうか
    bool IsAnimating() const { return animState == FORK_ANIM_STATE::APPEAR || animState == FORK_ANIM_STATE::DISAPPEAR; }
};