#include "TuningFork.h"
#include "../../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

TuningFork::TuningFork()
{
}

TuningFork::~TuningFork()
{
    // 自分が消えるときは、管理している子供たちも道連れにする
    for (auto eff : effects) {
        delete eff;
    }
    effects.clear();
}

void TuningFork::Init()
{
    p_transform->position.z = -2.0f;
    p_transform->scale = { 100.0f, 100.0f, 1.0f };

    auto renderer = GetComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/02-Player/TuningFork.png");

    // デフォルトはプレビュー用（半透明・非表示）
    renderer->GetPolygonRef().material.diffuse = { 1.0f, 1.0f, 0.0f, 0.5f };
    renderer->SetIsActive(false);
}

void TuningFork::Update()
{
    // 親クラス更新 (TrackObject)
    TrackObject::Update();

    // 子供たちの面倒を見る
    UpdateEffects();
}

void TuningFork::UpdateEffects()
{
    for (auto eff : effects)
    {
        if (eff->GetIsActive())
        {
            eff->Update();
        }
    }
}

void TuningFork::ShowAt(const hft::HFFLOAT2& _index)
{
    auto renderer = GetComponent<SpriteRenderer>();
    if (!renderer->GetIsActive()) {
        renderer->SetIsActive(true);
    }
    SetLineIndex(_index);
}

void TuningFork::Hide()
{
    GetComponent<SpriteRenderer>()->SetIsActive(false);
}

void TuningFork::PlayHitEffect()
{
    // 非表示で待機中のエフェクトを探す
    EffectFork* targetEffect = nullptr;

    for (auto eff : effects)
    {
        // Activeじゃない＝画面外に出て暇にしている
        if (!eff->GetIsActive())
        {
            targetEffect = eff;
            break;
        }
    }

    // もし見つからないなら、新しく作る
    if (targetEffect == nullptr)
    {
        std::cout << "new EffFork" << std::endl;
        targetEffect = new EffectFork();
        targetEffect->Init();
        effects.push_back(targetEffect); // リストに追加（これは最初だけ）
    }

    // 座標をセットして叩き起こす
    hft::HFFLOAT2 currentPos = { p_transform->position.x, p_transform->position.y };
    targetEffect->Setup(currentPos);

    // 自分（プレビュー）は隠れる
    Hide();
}