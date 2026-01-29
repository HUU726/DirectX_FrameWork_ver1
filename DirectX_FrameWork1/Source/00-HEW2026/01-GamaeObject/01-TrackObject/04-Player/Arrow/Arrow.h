#pragma once
#include "../../../../../99-Lib/01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"

class Arrow : public GameObject2D
{
private:
    float scaleRatio = 1.0f; //マップ比率保存用変数

public:
    Arrow();
    ~Arrow();

    void Init() override;
    void Init(float _scaleRatio);

    /**
     * @brief 矢印の状態を更新して表示
     * @param _pos   表示位置（音叉と同じ場所）
     * @param _angle 回転角度（度数法）
     * @param _ratio パワーの割合 (0.0f ~ 1.0f)
     */
    void UpdateTransform(const hft::HFFLOAT2& _pos, float _angle, float _ratio);

    void Hide();
};