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

    // ★修正：複雑な計算をやめて、パワーをそのままマスの数にする
    // "純粋に力とマスを対応させる" ならこれが一番キレイです。
    // パワー 3.5 = 3.5マス分
    float tileCount = _power;

    // ※もし「0.5マス」のような端数が嫌で、カクカク伸ばしたいなら
    // float tileCount = (float)((int)_power); 
    // にしてください。

    // 上限キャップ（Player側で999を渡しているので実質無効）
    if (tileCount > _maxDist)
    {
        tileCount = _maxDist;
    }

    // 計算したマス数 × タイルサイズ で実際の長さを出す
    float length = _tileSize * tileCount;

    // 最低保証（0だと見えなくなるので）
    if (length < 0.1f) length = 0.1f;

    pTrf->scale = { length, 50.f, 1.0f };

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