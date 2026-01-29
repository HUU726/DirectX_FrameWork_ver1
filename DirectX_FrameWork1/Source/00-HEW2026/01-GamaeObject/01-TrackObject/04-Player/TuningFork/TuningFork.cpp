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
    renderer->GetPolygonRef().material.diffuse = { 1.0f, 1.0f, 1.0f, 0.5f };
    renderer->SetIsActive(false);
}

void TuningFork::Init(float _scaleRatio)
{
    scaleRatio = _scaleRatio;

    p_transform->position.z = -2.0f;

    // 比率を掛ける
    p_transform->scale = { 100.0f * scaleRatio, 100.0f * scaleRatio, 1.0f };

    auto renderer = GetComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/02-Player/TuningFork.png");

    renderer->GetPolygonRef().material.diffuse = { 1.0f, 1.0f, 1.0f, 0.5f };
    renderer->SetIsActive(false);
}

void TuningFork::Update()
{
    // 親クラス更新
    TrackObject::Update();

    // 子供たちの面倒を見る
    UpdateEffects();

    // 設置/撤去アニメーション処理
    if (animState == FORK_ANIM_STATE::APPEAR)
    {
        animTimer++;
        float rate = (float)animTimer / ANIM_DURATION;
        if (rate >= 1.0f) rate = 1.0f;

        auto pTrf = GetTransformPtr();

        // 動きの計算: 上からスッと降りてくる
        // rate: 0.0 -> 1.0
        // オフセット: 50.0 -> 0.0
        float offset = (1.0f - rate) * 50.0f * scaleRatio;

        pTrf->position.x = targetPos.x;
        pTrf->position.y = targetPos.y + offset; // Y座標にオフセットを足す（画面上方向が+なら）

        // フェードイン: 0.0 -> 1.0
        SetAlpha(rate);

        // 終了判定
        if (animTimer >= ANIM_DURATION)
        {
            animState = FORK_ANIM_STATE::IDLE;
            pTrf->position.y = targetPos.y; // ズレ防止
            SetAlpha(1.0f);
        }
    }
    else if (animState == FORK_ANIM_STATE::DISAPPEAR)
    {
        animTimer++;
        float rate = (float)animTimer / ANIM_DURATION;
        if (rate >= 1.0f) rate = 1.0f;

        auto pTrf = GetTransformPtr();

        // 動きの計算: 上にスッと昇っていく
        // rate: 0.0 -> 1.0
        // オフセット: 0.0 -> 50.0
        float offset = rate * 50.0f * scaleRatio;

        pTrf->position.y = targetPos.y + offset;

        // フェードアウト: 1.0 -> 0.0
        SetAlpha(1.0f - rate);

        // 終了判定
        if (animTimer >= ANIM_DURATION)
        {
            animState = FORK_ANIM_STATE::NONE;
            Hide(); // 完全に消す
        }
    }
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
    // アニメーション中でなければ消す
    if (!IsAnimating())
    {
        GetComponent<SpriteRenderer>()->SetIsActive(false);
        SetAlpha(0.5f);
    }
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
        targetEffect->Init(scaleRatio);
        effects.push_back(targetEffect); // リストに追加（これは最初だけ）
    }

    // 座標をセットして叩き起こす
    hft::HFFLOAT2 currentPos = { p_transform->position.x, p_transform->position.y };
    targetEffect->Setup(currentPos);

    // 自分（プレビュー）は隠れる
    Hide();
}

void TuningFork::SetAlpha(float a)
{
    auto renderer = GetComponent<SpriteRenderer>();
    renderer->GetPolygonRef().material.diffuse = { 1.0f, 1.0f, 1.0f, a };
}

// 出現開始
void TuningFork::PlayAppear(const hft::HFFLOAT2& _pos)
{
    targetPos = _pos;
    animTimer = 0;
    animState = FORK_ANIM_STATE::APPEAR;

    // 強制的に表示ON
    GetComponent<SpriteRenderer>()->SetIsActive(true);
    // 初期位置セット（少し上）
    GetTransformPtr()->position.x = targetPos.x;
    GetTransformPtr()->position.y = targetPos.y + (50.0f * scaleRatio);
    SetAlpha(0.0f); // 最初は透明
}

// 消失開始
void TuningFork::PlayDisappear()
{
    // 現在位置を基準にする
    targetPos = { GetTransformPtr()->position.x, GetTransformPtr()->position.y };
    animTimer = 0;
    animState = FORK_ANIM_STATE::DISAPPEAR;
}