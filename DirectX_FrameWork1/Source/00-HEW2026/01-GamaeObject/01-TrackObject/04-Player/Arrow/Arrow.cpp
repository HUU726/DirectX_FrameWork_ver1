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

void Arrow::UpdateTransform(const hft::HFFLOAT2& _pos, float _angle, float _ratio, float _tileSize)
{
    auto renderer = GetComponent<SpriteRenderer>();
    if (!renderer->GetIsActive()) {
        renderer->SetIsActive(true);
    }

    Transform* pTrf = GetTransformPtr();

    // 回転の設定
    float rotDeg = _angle - 180.f;
    pTrf->rotation.z = rotDeg;

    // 長さ（スケール）の決定
    float length = _tileSize * (0.5f + _ratio * 2.0f);

    pTrf->scale = { length, 50.0f, 1.0f };

    // 位置のオフセット計算
    // 角度をラジアンに変換
    float rad = rotDeg * 3.14159265f / 180.0f;
    float dirX = std::cos(rad);
    float dirY = std::sin(rad);

    // ずらす距離 = (タイルの半径) + (矢印の半径)
    float offsetDist = (_tileSize * -0.2f) + (length * 0.5f);

    // 座標に反映
    pTrf->position.x = _pos.x + dirX * offsetDist;
    pTrf->position.y = _pos.y + dirY * offsetDist;
}

void Arrow::Hide()
{
    GetComponent<SpriteRenderer>()->SetIsActive(false);
}