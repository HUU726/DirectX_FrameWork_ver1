#pragma once

#include "../../../../../99-Lib/01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"

class EffectFork : public GameObject
{
private:
    float flySpeed;
    float rotateSpeed;
	hft::HFFLOAT2 baseScale;

public:
    EffectFork() : flySpeed(3.0f), rotateSpeed(18.0f), baseScale({ 100.f, 100.f }) {}
    ~EffectFork() {}

    void Init() override;   // 画像読み込みなど
	void Init(float _scaleRatio);
    void Update() override; // 飛ぶ処理

    // 飛ぶ方向などのセットアップ
    void Setup(const hft::HFFLOAT2& _startPos);
};