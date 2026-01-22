#include "EffectFork.h"
#include "../../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

// =========================================================
// 演出用クラス (EffectFork) の実装
// =========================================================
void EffectFork::Init()
{
    p_transform->scale = { 100.0f, 100.0f, 1.0f };
    p_transform->position.z = -5.0f; // 手前に表示

    auto renderer = AddComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/02-Player/TuningFork.png");

    // 最初から実体（不透明）
    renderer->GetPolygonRef().material.diffuse = { 1.0f, 1.0f, 0.0f, 1.0f };
}

void EffectFork::Setup(const hft::HFFLOAT2& _startPos)
{
    p_transform->position.x = _startPos.x;
    p_transform->position.y = _startPos.y;

    // 再利用のために状態をリセット
    p_transform->rotation.z = 0.0f; // 回転を0に戻す

    // 表示ON（GameObjectの機能で描画対象に戻す）
    SetIsActive(true);
    SetIsRender(true);

    // スプライトも念のためActiveに
    if (auto renderer = GetComponent<SpriteRenderer>())
    {
        renderer->SetIsActive(true);
    }
}

void EffectFork::Update()
{
    // 親クラス更新
    GameObject2D::Update();

    // 飛ぶ処理
    p_transform->position.y += flySpeed;
    p_transform->rotation.z += rotateSpeed;

    if (p_transform->position.y > 600.0f)
    {
        SetIsActive(false);
        SetIsRender(false);
    }
}