#include "PlayerObject.h"
#include "TuningFork/TuningFork.h" // 音叉クラス
#include "Arrow/Arrow.h"           // 矢印クラス

#include "../../../10-Map/00-BaseMap/BaseMap.h"

#include "../../../../04-Input/Input.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../../../99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"

#include <cmath>

#define CHARGE_THRESHOLD 0.2f
#define TILE_SIZE 100.0f
#define INVINCIBLE_TIME 1.0f

enum ANIM_ID {
    ANIM_STAND = 0,
    ANIM_CHARGE = 1,
    ANIM_SWING_H = 2,
    ANIM_SWING_V = 3,
    ANIM_HIT = 4,
    ANIM_DEAD =5
};

PlayerObject::PlayerObject()
    : hitpoint(3), hammer_power(0.0f), invincible(false), inv_time(0.0f)
    , state(PLAYER_STATE::STAND), animTimer(0)
    , pTuningFork(nullptr), pArrow(nullptr)
{

}

PlayerObject::~PlayerObject()
{
    if (pTuningFork) { delete pTuningFork; pTuningFork = nullptr; }
    if (pArrow) { delete pArrow; pArrow = nullptr; }
}

void PlayerObject::Init(BaseMap* _pMap, Input* _pInput)
{
    pMap = _pMap;
    pInput = _pInput;

    p_transform->scale = { 100.0f, 100.0f, 1.0f };

    // プレイヤー自身の初期化
    auto renderer = GetComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/99-Test/char01.png");

    hft::HFFLOAT2 div = { 3.0f, 4.0f };

    auto animator = AddComponent<SpriteAnimator>(div);

    // 引数: 分割数, 開始位置(x,y), コマ数
    // 立ち状態のアニメーション作成 (ANIM_STAND = 0)
    SpriteAnimation animStand(div, { 0.0f, 0.0f }, 3);
    for (int i = 0; i < 3; i++)
    {
        animStand.GetCellRef(i).flame = 15;
    }
    animStand.SetType(SPRITE_ANIM_TYPE::LOOP);
    animStand.SetID(ANIM_STAND);
    animator->AddAnimation(animStand);

    // 溜め状態 (ANIM_CHARGE = 1)
    SpriteAnimation animCharge(div, { 0.0f, 0.0f }, 3);
    for (int i = 0; i < 3; i++)
    {
        animCharge.GetCellRef(i).flame = 60;
    }
    animCharge.SetType(SPRITE_ANIM_TYPE::NORMAL);
    animCharge.SetID(ANIM_CHARGE);
    animator->AddAnimation(animCharge);

    // 横振り (ANIM_SWING_H = 2)
    SpriteAnimation animSwingH(div, { 1.0f, 0.0f }, 3);
    for (int i = 0; i < 3; i++)
    {
        animSwingH.GetCellRef(i).flame = 3;
    }
    animSwingH.SetType(SPRITE_ANIM_TYPE::NORMAL);
    animSwingH.SetID(ANIM_SWING_H);
    animator->AddAnimation(animSwingH);

    // 縦振り (ANIM_SWING_V = 3)
    SpriteAnimation animSwingV(div, { 1.0f, 0.0f }, 3);
    for (int i = 0; i < 3; i++)
    {
        animSwingV.GetCellRef(i).flame = 3;
    }
    animSwingV.SetType(SPRITE_ANIM_TYPE::NORMAL);
    animSwingV.SetID(ANIM_SWING_V);
    animator->AddAnimation(animSwingV);

    // 被弾 (ANIM_HIT = 4)
    SpriteAnimation animHit(div, { 0.0f, 0.0f }, 3);
    for (int i = 0; i < 3; i++)
    {
        animHit.GetCellRef(i).flame = 1;
    }
    animHit.SetType(SPRITE_ANIM_TYPE::LOOP);
    animHit.SetID(ANIM_HIT);
    animator->AddAnimation(animHit);

    // 被弾 (ANIM_DEAD = 5)
    SpriteAnimation animDead(div, { 0.0f, 0.0f }, 3);
    for (int i = 0; i < 3; i++)
    {
        animDead.GetCellRef(i).flame = 0;
    }
    animDead.SetType(SPRITE_ANIM_TYPE::LOOP);
    animDead.SetID(ANIM_HIT);
    animator->AddAnimation(animDead);

    // 最初に立ち状態を再生しておく
    animator->Play(ANIM_STAND);

    auto collider = AddComponent<BoxCollider2D>();
    collider->Init();
    collider->SetSize({ 50.0f, 50.0f, 0.0f });

    // 子オブジェクト生成
    pTuningFork = new TuningFork();
    pTuningFork->Init();

    pArrow = new Arrow();
    pArrow->Init();

}

void PlayerObject::Update()
{
    // 行動不能判定
    if (pMap)
    {
        hft::HFFLOAT2 myIndex = GetLineIndex();

        // 「有効なマスに乗っていない（＝動いている or 範囲外）」なら操作不能
        if (!pMap->IsValidTarget(myIndex))
        {
            if (state != PLAYER_STATE::STAND) ChangeState(PLAYER_STATE::STAND);

            if (pTuningFork) pTuningFork->Hide();
            if (pArrow) pArrow->Hide();
            return;
        }
    }

    // ステートマシン
    switch (state)
    {
    case PLAYER_STATE::STAND:   UpdateStand();   break;
    case PLAYER_STATE::SELECT:  UpdateSelect();  break;
    case PLAYER_STATE::CHARGE:  UpdateCharge();  break;
    case PLAYER_STATE::RELEASE: UpdateRelease(); break;
    case PLAYER_STATE::HIT:     UpdateDamage();  break;
    }

    // 子オブジェクト更新
    if (pTuningFork) pTuningFork->Update();
    if (pArrow) pArrow->Update();

    // 無敵時間更新
    if (invincible)
    {
        inv_time -= 1.0f / 60.0f;
        if (inv_time <= 0.0f)
        {
            invincible = false;
            GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,1,1,1 };
        }
        else
        {
            float alpha = (int)(inv_time * 20) % 2 == 0 ? 0.5f : 1.0f;
            GetComponent<SpriteRenderer>()->GetPolygonRef().material.diffuse = { 1,1,1,alpha };
        }
    }
}

// ----------------------------------------------------------------------------
// ステート別処理
// ----------------------------------------------------------------------------

void PlayerObject::UpdateStand()
{
    hft::HFFLOAT2 stick = pInput->GetLeftAnalogStick();
    if ((stick.x * stick.x + stick.y * stick.y) > 0.1f)
    {
        ChangeState(PLAYER_STATE::SELECT);
        std::cout << "STATE:PlayerStand >> PlayerSecect" << std::endl;
    }
}

void PlayerObject::UpdateSelect()
{
    hft::HFFLOAT2 stick = pInput->GetLeftAnalogStick();
    float magSq = stick.x * stick.x + stick.y * stick.y;

    // 向き変更
    if (magSq > 0.25f)
    {
        if (std::abs(stick.x) > std::abs(stick.y)) {
            angle.x = (stick.x > 0) ? 0.0f : 180.0f;
        }
        else {
            angle.x = (stick.y > 0) ? 90.0f : 270.0f;
        }
    }

    // ---------------------------------------------------
    // 判定：音叉を表示する予定のマス（プレイヤーの隣）をチェック
    // ---------------------------------------------------
    bool isTargetValid = false;

    // 自分の位置
    hft::HFFLOAT2 myIndex = GetLineIndex();
    // 向いている方向
    hft::HFFLOAT2 dirVec = GetVecFromAngle(angle.x);

    hft::HFFLOAT2 targetIndex = {
            myIndex.x + dirVec.x,
            myIndex.y + dirVec.y
    };

    if (pMap)
    {
        // マップに対して「ターゲットのマス(targetIndex)」が有効か聞く
        isTargetValid = pMap->IsValidTarget(targetIndex);
    }

    // ---------------------------------------------------
    // 音叉表示の制御
    // ---------------------------------------------------
    if (pTuningFork)
    {
        // ターゲットが有効な場合のみ表示
        if (isTargetValid)
        {
            // 画面上の座標計算
            hft::HFFLOAT2 myPos = { p_transform->position.x, p_transform->position.y };
            hft::HFFLOAT2 targetPos = {
                 myPos.x + (dirVec.x * TILE_SIZE),
                 myPos.y - (dirVec.y * TILE_SIZE)
            };

            pTuningFork->SetLineIndex(targetIndex);
            pTuningFork->GetTransformPtr()->position.x = targetPos.x;
            pTuningFork->GetTransformPtr()->position.y = targetPos.y;
            pTuningFork->GetComponent<SpriteRenderer>()->SetIsActive(true);
        }
        else
        {
            // 無効（壁の外 or スライド中）なら隠す
            pTuningFork->Hide();
        }
    }

    // ---------------------------------------------------
    // 遷移判定
    // ---------------------------------------------------
    if (pInput->GetButtonPress(Button::XBox::X))
    {
        // ターゲットが有効、かつ入力が十分ならチャージへ
        if (isTargetValid && magSq > CHARGE_THRESHOLD * CHARGE_THRESHOLD)
        {
            ChangeState(PLAYER_STATE::CHARGE);
            std::cout << "STATE:PlayerSelect >> PlayerCharge";
        }
    }
    else if (magSq < 0.01f)
    {
        ChangeState(PLAYER_STATE::STAND);
        if (pTuningFork) pTuningFork->Hide();
        std::cout << "STATE:PlayerSelect >> PlayerStand";
    }
}

void PlayerObject::UpdateCharge()
{
    hft::HFFLOAT2 stick = pInput->GetLeftAnalogStick();
    float mag = std::sqrt(stick.x * stick.x + stick.y * stick.y);

    // キャンセル判定
    if (mag < CHARGE_THRESHOLD)
    {
        hammer_power = 0.0f;
        if (!pInput->GetButtonPress(Button::XBox::X)) {
            ChangeState(PLAYER_STATE::SELECT);
            std::cout << "STATE:PlayerCharge >> PlayerSecect" << std::endl;
        }
        if (pArrow) pArrow->Hide(); // 隠すだけ
        return;
    }

    // パワー計算
    hammer_power = mag * max_hammer_power;
    if (hammer_power > max_hammer_power) hammer_power = max_hammer_power;

    // 矢印表示の制御
    if (pArrow && pTuningFork)
    {
        float angle = 0.0f;

        // 90度で固定
        if (std::abs(stick.x) > std::abs(stick.y)) {
            angle = (stick.x > 0) ? 0.0f : 180.0f; // 右 or 左
        }
        else {
            angle = (stick.y > 0) ? 90.0f : 270.0f;
        }

        // 後ろ向き判定
        // 矢印の角度とプレイヤーの向き(this->angle.x)の差をチェック
        float angleDiff = std::abs(angle - this->angle.x);
        // 360度ループ対策 (例: 0度と270度の差は90度)
        if (angleDiff > 180.0f) angleDiff = 360.0f - angleDiff;

        // 差がほぼ180度（真後ろ）なら表示しない
        if (std::abs(angleDiff - 180.0f) < 1.0f)
        {
            pArrow->Hide();
        }
        else
        {
            // それ以外（正面・横）なら表示
            float ratio = hammer_power / max_hammer_power;
            hft::HFFLOAT2 targetPos = {
                pTuningFork->GetTransformPtr()->position.x,
                pTuningFork->GetTransformPtr()->position.y
            };
            pArrow->UpdateTransform(targetPos, angle, ratio);
        }
    }

    // 発動判定
    if (!pInput->GetButtonPress(Button::XBox::X))
    {
        ChangeState(PLAYER_STATE::RELEASE);
        std::cout << "STATE:PlayerCharge >> PlayerReleace" << std::endl;
    }
}

void PlayerObject::UpdateRelease()
{
    animTimer++;

    hft::HFFLOAT2 stick = pInput->GetLeftAnalogStick();

    // ---------------------------------------------------
    // 1フレーム目：入力チェック & アニメ開始
    // ---------------------------------------------------
    if (animTimer == 1)
    {
        // スティック入力がない場合は攻撃キャンセル
        if (std::abs(stick.x) <= 0.1f && std::abs(stick.y) <= 0.1f)
        {
            ChangeState(PLAYER_STATE::STAND);

            // 演出を消して終了
            if (pTuningFork) pTuningFork->Hide();
            if (pArrow) pArrow->Hide();
            hammer_power = 0.0f;
            return;
        }

        // 移動ベクトル計算
        hft::HFFLOAT2 moveVec = { 0, 0 };
        if (std::abs(stick.x) > std::abs(stick.y)) {
            moveVec.x = (stick.x > 0) ? 1.0f : -1.0f;
        }
        else {
            moveVec.y = (stick.y > 0) ? -1.0f : 1.0f;
        }

        // 逆方向（バック）判定
        hft::HFFLOAT2 playerDir = GetVecFromAngle(angle.x);
        if (moveVec.x == -playerDir.x && moveVec.y == -playerDir.y)
        {
            // 後ろ入力なら攻撃中止
            ChangeState(PLAYER_STATE::STAND);
            std::cout << "Action: Cancel (Backward Input)" << std::endl;

            if (pTuningFork) pTuningFork->Hide();
            if (pArrow) pArrow->Hide();
            hammer_power = 0.0f;
            return;
        }

        // アニメーション分岐（縦・横）
        if (moveVec.x == playerDir.x && moveVec.y == playerDir.y)
        {
            GetComponent<SpriteAnimator>()->Play(ANIM_SWING_V);
            std::cout << "Anim:SwingV (Forward)" << std::endl;
        }
        else
        {
            GetComponent<SpriteAnimator>()->Play(ANIM_SWING_H);
            std::cout << "Anim:SwingH (Side)" << std::endl;
        }

        // 演出用オブジェクトを隠す
        if (pTuningFork) pTuningFork->Hide();
        if (pArrow) pArrow->Hide();
    }

    // ---------------------------------------------------
    // 攻撃開始フレーム目：スライド実行＆中断チェック
    // ---------------------------------------------------
    if (animTimer == SLIDE_TIMING)
    {
        // 入力がなくなっていたり、後ろ入力になっていたら中断（キャンセル）

        bool isNeutral = (std::abs(stick.x) <= 0.1f && std::abs(stick.y) <= 0.1f);
        bool isBackStep = false;

        hft::HFFLOAT2 moveVec = { 0, 0 };

        if (!isNeutral)
        {
            // 入力方向を計算
            if (std::abs(stick.x) > std::abs(stick.y)) {
                moveVec.x = (stick.x > 0) ? 1.0f : -1.0f;
            }
            else {
                moveVec.y = (stick.y > 0) ? -1.0f : 1.0f;
            }

            // バックステップ判定
            hft::HFFLOAT2 playerDirMap = GetVecFromAngle(angle.x);
            if (moveVec.x == -playerDirMap.x && moveVec.y == -playerDirMap.y) {
                isBackStep = true;
            }
        }

        // 中断判定
        if (isNeutral || isBackStep)
        {
            // アニメーションごと強制キャンセルして立ちに戻す
            ChangeState(PLAYER_STATE::STAND);
            std::cout << "Action: Cancel (Input Lost or Invalid)" << std::endl;

            // アニメも立ちに戻す（一応明示的に）
            auto animator = GetComponent<SpriteAnimator>();
            animator->Play(ANIM_STAND);

            hammer_power = 0.0f;
            return;
        }

        // ここまで来たらスライド実行
        if (pMap)
        {
            hft::HFFLOAT2 anchorIdx = GetTargetIndex();
            try
            {
                if (anchorIdx.x >= 0 && anchorIdx.y >= 0) {
                    pMap->SetSlideData(anchorIdx, moveVec, hammer_power);
                    if (pTuningFork) pTuningFork->PlayHitEffect();
                    std::cout << "Action: Slide!" << std::endl;
                }
            }
            catch (const std::out_of_range&) {
                std::cout << "Action: Cancel (Exception)" << std::endl;
            }
        }
        hammer_power = 0.0f;
    }

    // ---------------------------------------------------
    // 終了判定
    // ---------------------------------------------------
    if (animTimer > ANIM_END_TIME)
    {
        ChangeState(PLAYER_STATE::STAND);
        std::cout << "STATE:PlayerRelease >> PlayerStand" << std::endl;

        auto animator = GetComponent<SpriteAnimator>();
        animator->Play(ANIM_STAND);
    }
}

void PlayerObject::UpdateDamage()
{
    if (!invincible) ChangeState(PLAYER_STATE::STAND);
    std::cout << "STATE:Hit >> Stand" << std::endl;
}

void PlayerObject::OnHit()
{
    hitpoint--;
    std::cout << "Player Damaged! HP:" << hitpoint << std::endl;

    if (hitpoint <= 0)
    {
        OnDead();
    }
    else
    {
        invincible = true;
        inv_time = INVINCIBLE_TIME;

        // ステート変更
        ChangeState(PLAYER_STATE::HIT);
        std::cout << "STATE: PlayerHit" << std::endl;
    }
}

void PlayerObject::OnDead()
{
    ChangeState(PLAYER_STATE::DEAD);
    std::cout << "STATE: PlayerDEAD" << std::endl;

    // ここにゲームオーバー処理などを追加
}

void PlayerObject::OnCollisionEnter2D(Collider2D* _p_col)
{
    // 無敵中や死亡中は無視
    if (invincible || state == PLAYER_STATE::DEAD) return;

    // 相手のタグを取得
    std::string tag = _p_col->GetGameObject()->GetTag();

    // 敵やダメージ床に触れたら OnHit を呼ぶ
    if (tag == "Enemy" || tag == "DamageObject")
    {
        OnHit();
    }
}

// ----------------------------------------------------------------------------
// ヘルパー関数
// ----------------------------------------------------------------------------

void PlayerObject::ChangeState(PLAYER_STATE _nextState)
{
    auto animator = GetComponent<SpriteAnimator>();

    //今のステートのアニメーションを止める
    switch (state) {
    case PLAYER_STATE::STAND:
        //animator->Stop(ANIM_STAND); 
        break;

    case PLAYER_STATE::CHARGE:
        animator->Stop(ANIM_CHARGE);
        break;

    case PLAYER_STATE::HIT:
        animator->Stop(ANIM_HIT);
        break;

    case PLAYER_STATE::RELEASE:
        animator->Stop(ANIM_SWING_H);
        animator->Stop(ANIM_SWING_V);
        break;
    }

    state = _nextState; //ステート更新
    animTimer = 0;

    //次ステートのアニメーション再生
    switch (state) {
    case PLAYER_STATE::STAND:   animator->Play(ANIM_STAND); break;
    case PLAYER_STATE::CHARGE:  animator->Play(ANIM_CHARGE); break;
    case PLAYER_STATE::HIT:     animator->Play(ANIM_HIT); break;
    default: break;
    }
}

hft::HFFLOAT2 PlayerObject::GetTargetIndex() const
{
    hft::HFFLOAT2 current = const_cast<PlayerObject*>(this)->GetLineIndex();
    hft::HFFLOAT2 dir = GetVecFromAngle(angle.x);

    return { current.x + dir.x, current.y + dir.y };
}

hft::HFFLOAT2 PlayerObject::GetVecFromAngle(float _angle) const
{
    int a = (int)_angle % 360;
    if (a < 0) a += 360;

    if (a == 0)   return { 1.0f,  0.0f }; // 右
    if (a == 90)  return { 0.0f, -1.0f }; // 上
    if (a == 180) return { -1.0f,  0.0f }; // 左
    if (a == 270) return { 0.0f,  1.0f }; // 下
    return { 1.0f, 0.0f };
}

float PlayerObject::GetAngleFromVec(hft::HFFLOAT2 _vec) const
{
    return std::atan2(_vec.y, _vec.x) * 180.0f / 3.14159265f;
}