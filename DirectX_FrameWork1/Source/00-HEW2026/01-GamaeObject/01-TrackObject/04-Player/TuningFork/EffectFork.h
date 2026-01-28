#pragma once

#include "../../../../../99-Lib/01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"

class EffectFork : public GameObject
{
private:
    float flySpeed;
    float rotateSpeed;

public:
    EffectFork() : flySpeed(5.0f), rotateSpeed(20.0f) {}
    ~EffectFork() {}

    void Init() override;   // 画像読み込みなど
    void Update() override; // 飛ぶ処理

    // 飛ぶ方向などのセットアップ
    void Setup(const hft::HFFLOAT2& _startPos);
};