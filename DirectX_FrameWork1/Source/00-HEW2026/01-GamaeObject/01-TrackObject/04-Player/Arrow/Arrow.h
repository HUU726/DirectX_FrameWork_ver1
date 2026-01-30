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
         * @param _pos      表示位置
         * @param _angle    角度
         * @param _ratio    パワー割合
         * @param _power    パワー絶対値
         * @param _tileSize タイルサイズ
         * @param _maxDist  最大距離（マス数）
         */
    void UpdateTransform(const hft::HFFLOAT2& _pos, float _angle, float _ratio, float _power, float _tileSize, float _maxDist);

    void Hide();
};