#include "EffectFork.h"
#include "../../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

// =========================================================
// 演出用クラス (EffectFork) の実装
// =========================================================
void EffectFork::Init()
{
    p_transform->scale = { 100.0f, 100.0f, 1.0f };
    baseScale = p_transform->scale;

    p_transform->position.z = -5.0f; // 手前に表示

    auto renderer = AddComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/02-Player/TuningFork.png");

    // 最初から実体（不透明）
    renderer->GetPolygonRef().material.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void EffectFork::Init(float _scaleRatio)
{
    // 比率を掛ける
    p_transform->scale = { 100.0f * _scaleRatio, 100.0f * _scaleRatio, 1.0f };
    baseScale = p_transform->scale;

    p_transform->position.z = -5.0f;

    auto renderer = AddComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/02-Player/TuningFork.png");

    renderer->GetPolygonRef().material.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void EffectFork::Setup(const hft::HFFLOAT2& _startPos)
{
    p_transform->position.x = _startPos.x;
    p_transform->position.y = _startPos.y;

    // 再利用のために状態をリセット
    p_transform->rotation.z = 0.0f; // 回転を0に戻す
	p_transform->scale = baseScale; // スケールを元に戻す

    // 表示ON（GameObjectの機能で描画対象に戻す）
    SetIsActive(true);
    SetIsRender(true);

    // スプライトも念のためActiveに
    if (auto renderer = GetComponent<SpriteRenderer>())
    {
        renderer->SetIsActive(true);
        renderer->GetPolygonRef().material.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
    }
}

void EffectFork::Update()
{
    // 動きの演出
    // 上昇 (ちょっと加速させてもいいかも)
    p_transform->position.y += flySpeed * 1.5f;

    // ゆらゆらさせる (Sin波でX座標を揺らす)
    // 係数(0.05f)を変えると揺れの速さ、(5.0f)を変えると揺れ幅が変わります
    float wobble = std::sin(p_transform->position.y * 0.1f) * 5.0f;
    p_transform->position.x += wobble;

    // 回転
    p_transform->rotation.z += rotateSpeed;

    // 拡大 (空へ上がっていく感じ)
    p_transform->scale.x *= 1.01f;
    p_transform->scale.y *= 1.01f;

    // フェードアウト (透明にしていく)
    auto renderer = GetComponent<SpriteRenderer>();
    float& alpha = renderer->GetPolygonRef().material.diffuse.w;

    alpha -= 0.01f;

    // 終了判定 (透明になりきったら消す)
    if (alpha <= 0.0f)
    {
        SetIsActive(false);
        SetIsRender(false);
    }
}