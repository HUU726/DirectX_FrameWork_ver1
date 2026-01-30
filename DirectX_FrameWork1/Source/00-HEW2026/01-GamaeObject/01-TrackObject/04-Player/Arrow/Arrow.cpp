#include "Arrow.h"
#include "../../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

void Arrow::Init()
{
    p_transform->position.z = -3.0f;

    p_transform->scale = { 100.0f, 100.0f, 1.0f };

    auto renderer = GetComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/02-Player/Arrow.png");

    renderer->SetIsActive(false);
}

void Arrow::Init(float _scaleRatio)
{
    scaleRatio = _scaleRatio;

    p_transform->position.z = -3.0f;

    // 比率を掛ける
    p_transform->scale = { 100.0f * scaleRatio, 100.0f * scaleRatio, 1.0f };

    auto renderer = GetComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/02-Player/Arrow.png");

    renderer->SetIsActive(false);
}

void Arrow::UpdateTransform(const hft::HFFLOAT2& _pos, float _angle, float _ratio, float _power, float _tileSize, float _maxDist) 
{
    auto renderer = GetComponent<SpriteRenderer>();
    if (!renderer->GetIsActive()) {
        renderer->SetIsActive(true);
    }

    Transform* pTrf = GetTransformPtr();

    // 1. 回転の設定
    float rotDeg = _angle - 180.f;
    pTrf->rotation.z = rotDeg;

    // 2. 長さ（スケール）の決定
    // 力(_power)に応じた長さを計算する
    float tileCount = 0.0f;

    if (_power <= 1.0f)
    {
        // 0～1まではリニア
        tileCount = _power;
    }
    else
    {
        int floorP = (int)_power; // 整数部 (例: 2.5 -> 2)
        float frac = _power - floorP; // 小数部 (例: 2.5 -> 0.5)

        // 整数部が奇数か偶数かで伸び率を変える
        if (floorP % 2 != 0) // 奇数 (1, 3, 5...) → 次は偶数 (+1ペース)
        {
            // 現在の到達マス数: L(k) = 1.5k - 0.5
            // 例: k=1 -> 1, k=3 -> 4, k=5 -> 7
            float currentLen = 1.5f * floorP - 0.5f;

            // 次の整数までは +1 ペースで伸びる
            tileCount = currentLen + frac * 1.0f;
        }
        else // 偶数 (2, 4, 6...) → 次は奇数 (+2ペース)
        {
            // 現在の到達マス数: L(k) = 1.5k - 1.0
            // 例: k=2 -> 2, k=4 -> 5, k=6 -> 8
            float currentLen = 1.5f * floorP - 1.0f;

            // 次の整数までは +2 ペースで伸びる
            tileCount = currentLen + frac * 2.0f;
        }
    }

    if (tileCount > _maxDist)
    {
        tileCount = _maxDist;
    }

    // 計算したマス数 × タイルサイズ で実際の長さを出す
    float length = _tileSize * tileCount;

    // もし最小表示サイズなどを保証したい場合はここで補正
    if (length < 0.1f) length = 0.1f;

    pTrf->scale = { length, 50.0f, 1.0f };

    // 3. 位置のオフセット計算
    float rad = rotDeg * 3.14159265f / 180.0f;
    float dirX = std::cos(rad);
    float dirY = std::sin(rad);

    // 長さの半分だけずらして、根本を合わせる
    float offsetDist = length * 0.5f;

    pTrf->position.x = _pos.x + dirX * offsetDist;
    pTrf->position.y = _pos.y + dirY * offsetDist;
}

void Arrow::Hide()
{
    GetComponent<SpriteRenderer>()->SetIsActive(false);
}