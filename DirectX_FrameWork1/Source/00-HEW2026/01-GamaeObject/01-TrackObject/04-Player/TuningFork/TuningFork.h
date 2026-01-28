#pragma once
#include "../../../../../99-Lib/01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"
#include "../../00-TrackObject/TrackObject.h"
#include "EffectFork.h"

class TuningFork : public TrackObject
{
private:
    std::vector<EffectFork*> effects;

    void UpdateEffects();

public:
    TuningFork();
    ~TuningFork();

    void Init() override;
    void Update() override;

    void ShowAt(const hft::HFFLOAT2& _index);
    void Hide();

    void PlayHitEffect();

    void SetAlpha(float a);
};