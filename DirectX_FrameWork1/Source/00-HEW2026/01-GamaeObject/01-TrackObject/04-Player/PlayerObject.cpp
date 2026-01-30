#include "PlayerObject.h"
#include "TuningFork/TuningFork.h" // 音叉クラス
#include "Arrow/Arrow.h"           // 矢印クラス

#include "../../../10-Map/00-BaseMap/BaseMap.h"

#include "../../../../04-Input/Input.h"
#include "../../../../99-Lib/01-MyLib/03-Sound/Fsound.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../../../99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

#define CHARGE_THRESHOLD 0.2f
//#define TILE_SIZE 100.0f
//#define INVINCIBLE_TIME 1.0f

enum ANIM_ID {
    ANIM_STAND = 0,
    ANIM_CHARGE,
	ANIM_CHARGE_LOOP,
    ANIM_ATTACK_FRONT, // 正面
    ANIM_ATTACK_RIGHT, // 右方向
    ANIM_ATTACK_LEFT,  // 左方向
    ANIM_HIT,
    ANIM_DEAD,
    ANIM_DEAD_LOOP
};

PlayerObject::PlayerObject()
{
    tag = "Player";
	state = PLAYER_STATE::STAND;
	animTimer = 0;
}

PlayerObject::~PlayerObject()
{
    if (pTuningFork) { delete pTuningFork; pTuningFork = nullptr; }
    if (pArrow) { delete pArrow; pArrow = nullptr; }
}

void PlayerObject::Init(BaseMap* _pMap, Input* _pInput)
{
    //マウス入力モードで開始
	mouseMode = true;
    
    pMap = _pMap;
    pInput = _pInput;

    p_transform->scale = { 200.0f, 200.0f, 1.0f };

    // プレイヤー自身の初期化
    auto renderer = GetComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/02-Player/Ritu_animations.png");

    hft::HFFLOAT2 div = { 8.0f, 8.0f };

    auto animator = AddComponent<SpriteAnimator>(div);

    // 引数: 分割数, 開始位置(x,y), コマ数
    // 立ち状態のアニメーション作成 (ANIM_STAND = 0)
    SpriteAnimation animStand(div, { 0.0f, 0.0f }, 10);
    for (int i = 0; i < 10; i++)
    {
        animStand.GetCellRef(i).flame = 6;
    }
    animStand.SetType(SPRITE_ANIM_TYPE::LOOP);
    animStand.SetID(ANIM_STAND);
    animator->AddAnimation(animStand);

    // 溜め状態 (ANIM_CHARGE)
    SpriteAnimation animCharge(div, { 0.0f, 3.0f }, 16);
    for (int i = 0; i < 16; i++)
    {
        animCharge.GetCellRef(i).flame = chargeflame;
    }
    animCharge.SetType(SPRITE_ANIM_TYPE::NORMAL);
    animCharge.SetID(ANIM_CHARGE);
    animator->AddAnimation(animCharge);

	// 溜め状態ループ (ANIM_CHARGE_LOOP)
	SpriteAnimation animChargeLoop(div, { 3.0f, 4.0f }, 5);
    for(int i = 0; i < 5; i++)
    {
        animChargeLoop.GetCellRef(i).flame = 3;
	}
	animChargeLoop.SetType(SPRITE_ANIM_TYPE::LOOP);
	animChargeLoop.SetID(ANIM_CHARGE_LOOP);
	animator->AddAnimation(animChargeLoop);

    // 正面攻撃 (ANIM_ATTACK_FRONT)
    SpriteAnimation animFront(div, { 0.0f, 5.0f }, 4);
    for (int i = 0; i < 4; i++) 
    { 
        animFront.GetCellRef(i).flame = 3;
    }
    animFront.GetCellRef(3).flame = 15;
    animFront.SetType(SPRITE_ANIM_TYPE::NORMAL);
    animFront.SetID(ANIM_ATTACK_FRONT);
    animator->AddAnimation(animFront);

    // 右攻撃 (ANIM_ATTACK_RIGHT)
    SpriteAnimation animRight(div, { 7.0f, 5.0f }, 4);
    for (int i = 0; i < 4; i++)
    {
        animRight.GetCellRef(i).flame = 3;
    }
    animRight.GetCellRef(3).flame = 15;
    animRight.SetType(SPRITE_ANIM_TYPE::NORMAL);
    animRight.SetID(ANIM_ATTACK_RIGHT);
    animator->AddAnimation(animRight);

    // 左攻撃 (ANIM_ATTACK_LEFT)
    SpriteAnimation animLeft(div, { 6.0f, 6.0f }, 4);
    for (int i = 0; i < 4; i++)
    {
        animLeft.GetCellRef(i).flame = 3;
    }
    animLeft.GetCellRef(3).flame = 15;
    animLeft.SetType(SPRITE_ANIM_TYPE::NORMAL);
    animLeft.SetID(ANIM_ATTACK_LEFT);
    animator->AddAnimation(animLeft);

    // 被弾 (ANIM_HIT)
    SpriteAnimation animHit(div, { 2.0f, 1.0f }, 7);
    for (int i = 0; i < 7; i++)
    {
        animHit.GetCellRef(i).flame = 4;
    }
    animHit.SetType(SPRITE_ANIM_TYPE::NORMAL);
    animHit.SetID(ANIM_HIT);
    animator->AddAnimation(animHit);

    // ミス (ANIM_DEAD)
    SpriteAnimation animDead(div, { 1.0f, 2.0f }, 7);
    for (int i = 0; i < 7; i++)
    {
        animDead.GetCellRef(i).flame = 6;
    }
    animDead.SetType(SPRITE_ANIM_TYPE::NORMAL);
    animDead.SetID(ANIM_DEAD);
    animator->AddAnimation(animDead);

    SpriteAnimation animDeadLoop(div, { 7.0f, 2.0f }, 1);
    animDeadLoop.GetCellRef(0).flame = 1;
    animDeadLoop.SetType(SPRITE_ANIM_TYPE::LOOP);
    animDeadLoop.SetID(ANIM_DEAD_LOOP);
    animator->AddAnimation(animDeadLoop);

    // 最初に立ち状態を再生しておく
    animator->Play(ANIM_STAND);

    auto collider = AddComponent<BoxCollider2D>();
    collider->Init();
    collider->SetSize({ 50.0f, 50.0f, 0.0f });

    // 子オブジェクト生成
    float ratio = pMap->GetScaleRatio(); // マップ比率取得
    tileSize = 125.0f * ratio;

    pTuningFork = new TuningFork();
    pTuningFork->Init(ratio);

    pArrow = new Arrow();
    pArrow->Init(ratio);

	// サウンド読み込み
    SE_LAttack = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/00-Test/SE_Land.wav", false);
    SE_MAttack = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/00-Test/SE_Land.wav", false);
    SE_SAttack = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/00-Test/SE_Land.wav", false);
    SE_Charge = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/00-Test/SE_Land.wav", false);
    SE_Hit = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/00-Test/SE_Land.wav", false);
    SE_Dead = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/00-Test/SE_Land.wav", false);
}

void PlayerObject::Update()
{ 
    // 無敵時間更新
    if (invincible)
    {
        auto renderer = GetComponent<SpriteRenderer>();

        inv_cnt -= 1.0f / 60.0f;
        if (inv_cnt <= 0.0f)
        {
            invincible = false;
            //renderer->GetPolygonRef().material.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
			renderer->SetIsActive(true);
        }
        else
        {
            float alpha = (int)(inv_cnt * 8) % 2 == 0 ? 0.0f : 1.0f;
            //renderer->GetPolygonRef().material.diffuse = { 1.0f, 1.0f, 1.0f, alpha };
			renderer->SetIsActive(alpha);
        }
    }

    hft::HFFLOAT2 stick = pInput->GetLeftAnalogStick();
    float stickMagSq = stick.x * stick.x + stick.y * stick.y;

    if (stickMagSq > 0.1f)
    {
        controllerMode = true;
        mouseMode = false;
    }
    else if (pInput->GetMouseTrigger(Button::Mouse::Left))
    {
        controllerMode = false;
        mouseMode = true;
    }
    //std::cout << "ControllerMode:" << controllerMode << " MouseMode:" << mouseMode << std::endl;


    // 行動不能判定
    if (pMap)
    {
        hft::HFFLOAT2 myIndex = GetLineIndex();

        // 「有効なマスに乗っていない（＝動いている or 範囲外）」なら操作不能
        if (!pMap->IsValidTarget(myIndex))
        {
            if (state != PLAYER_STATE::STAND && state != PLAYER_STATE::RELEASE)
            {
                ChangeState(PLAYER_STATE::STAND);
            }

            if (pTuningFork) pTuningFork->Hide();
            if (pArrow) pArrow->Hide();

            if (state != PLAYER_STATE::RELEASE) return;
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
    case PLAYER_STATE::DEAD:    UpdateDead();    break;
    }

    // 子オブジェクト更新
    if (pTuningFork) pTuningFork->Update();
    if (pArrow) pArrow->Update();
}

// ----------------------------------------------------------------------------
// ステート別処理
// ----------------------------------------------------------------------------

void PlayerObject::UpdateStand()
{
    // コントローラー入力チェック
    hft::HFFLOAT2 stick = pInput->GetLeftAnalogStick();
    float stickMagSq = stick.x * stick.x + stick.y * stick.y;

    // マウス入力チェック（プレイヤー基準）
    // ---------------------------------------------------
    float mx = (float)pInput->GetMouseCenterX();
    float my = (float)pInput->GetMouseCenterY();

    // マウス位置 - 中心位置 = 相対ベクトル
    float relX = mx;
    float relY = my * -1.f;

    float mouseMagSq = relX * relX + relY * relY;

    // ---------------------------------------------------

    // スティック入力がある or マウスがプレイヤーからある程度離れているなら
    if (stickMagSq > 0.1f || mouseMagSq > 10.0f)
    {
        ChangeState(PLAYER_STATE::SELECT);
        std::cout << "STATE:PlayerStand >> PlayerSelect" << std::endl;
    }
}

void PlayerObject::UpdateSelect()
{
    // ---------------------------------------------------
    // 向きの決定 (コントローラー優先)
    // ---------------------------------------------------
    hft::HFFLOAT2 stick = pInput->GetLeftAnalogStick();
    float stickMagSq = stick.x * stick.x + stick.y * stick.y;

    // マウス座標取得（絶対座標：ドラッグ開始位置の記録用）
    float rawMx = (float)pInput->GetMouseCenterX();
    float rawMy = (float)pInput->GetMouseCenterY();

    // コントローラー入力がある場合
    if (stickMagSq > 0.25f && controllerMode)
    {
        if (std::abs(stick.x) > std::abs(stick.y)) {
            angle.x = (stick.x > 0) ? 0.0f : 180.0f;
        }
        else {
            angle.x = (stick.y > 0) ? 90.0f : 270.0f;
        }
    }
    // マウス操作の場合
    else if (mouseMode)
    {
        // マウスの絶対座標（画面中央が 0,0）
        float mouseWorldX = rawMx;
        float mouseWorldY = rawMy * -1.f;

        // プレイヤーの絶対座標（画面中央が 0,0）
        float playerWorldX = p_transform->position.x;
        float playerWorldY = p_transform->position.y;

        // 「プレイヤーから見た」マウスの位置（相対ベクトル）
        float relMx = mouseWorldX - playerWorldX;
        float relMy = mouseWorldY - playerWorldY;


        std::cout << "playerWorldX : " << playerWorldX << std::endl;
        std::cout << "playerWorldY : " << playerWorldY << std::endl;

        std::cout << "mouseWorldX : " << mouseWorldX << std::endl;
        std::cout << "mouseWorldY : " << mouseWorldY << std::endl;

        std::cout << "relMX : " << relMx << std::endl;
        std::cout << "relMY : " << relMy << std::endl;

        float distSq = relMx * relMx + relMy * relMy;

        // 半径20px以上離れていたら判定する
        if (distSq > 400.0f)
        {
            float targetAngle = angle.x;

            // XとYの絶対値を比べて、エリアを判定
            if (std::abs(relMx) > std::abs(relMy))
            {
                // 横長のエリアにいる（右か左）
                targetAngle = (relMx > 0) ? 0.0f : 180.0f;
            }
            else
            {
                // 縦長のエリアにいる（上か下）
                targetAngle = (relMy > 0) ? 90.0f : 270.0f;
            }

            // 有効判定
            hft::HFFLOAT2 dir = GetVecFromAngle(targetAngle);
            hft::HFFLOAT2 currentIdx = GetLineIndex();
            hft::HFFLOAT2 targetIdx = { currentIdx.x + dir.x, currentIdx.y + dir.y };

            if (pMap && pMap->IsValidTarget(targetIdx))
            {
                angle.x = targetAngle;
            }
        }
    }

    // ---------------------------------------------------
    // 音叉プレビュー表示
    // ---------------------------------------------------
    pTuningFork->SetAlpha(0.5f); //プレビュー用に半透明にする

    bool isTargetValid = false;
    hft::HFFLOAT2 myIndex = GetLineIndex();
    hft::HFFLOAT2 dirVec = GetVecFromAngle(angle.x);
    hft::HFFLOAT2 targetIndex = { myIndex.x + dirVec.x, myIndex.y + dirVec.y };

    if (pMap) isTargetValid = pMap->IsValidTarget(targetIndex);

    if (pTuningFork)
    {
        if (!pTuningFork->IsAnimating())
        {
            if (isTargetValid)
            {
                hft::HFFLOAT2 myPos = { p_transform->position.x, p_transform->position.y };
                hft::HFFLOAT2 targetPos = {
                     myPos.x + (dirVec.x * tileSize),
                     myPos.y - (dirVec.y * tileSize)
                };
                pTuningFork->SetLineIndex(targetIndex);
                pTuningFork->GetTransformPtr()->position.x = targetPos.x;
                pTuningFork->GetTransformPtr()->position.y = targetPos.y;
                pTuningFork->GetTransformPtr()->position.z = -10;
                pTuningFork->GetComponent<SpriteRenderer>()->SetIsActive(true);
            }
            else
            {
                pTuningFork->Hide();
            }
        }
    }

    // ---------------------------------------------------
    // チャージ開始判定
    // ---------------------------------------------------

    // コントローラー (Xボタン)
    if (pInput->GetButtonPress(Button::XBox::X) && controllerMode)
    {
        if (isTargetValid && stickMagSq > CHARGE_THRESHOLD * CHARGE_THRESHOLD)
        {
            mouseMode = false;
            ChangeState(PLAYER_STATE::CHARGE);
            std::cout << "STATE: Select >> Charge (Controller)" << std::endl;
        }
    }
    // マウス (左クリック)
    else if (pInput->GetMouseTrigger(Button::Mouse::Left) && mouseMode)
    {
        if (isTargetValid)
        {
            mouseMode = true;

            // ドラッグ計算用には絶対座標を使う
            dragStartPos.x = rawMx;
            dragStartPos.y = rawMy;

            ChangeState(PLAYER_STATE::CHARGE);
            std::cout << "STATE: Select >> Charge (Mouse)" << std::endl;
        }
    }
    else if (stickMagSq < 0.01f && controllerMode)
    {
        ChangeState(PLAYER_STATE::STAND);
        if (pTuningFork) pTuningFork->Hide();
    }
}

void PlayerObject::UpdateCharge()
{
    //SoundManager::GetInstance().Play(SE_Charge); // チャージ音再生

    animTimer++;
    if (!isChargeLoop)
    {
        const int CHARGE_START_DURATION = 16 * chargeflame;

        // 開始アニメが終わったらループに切り替え
        if (animTimer >= CHARGE_START_DURATION - 1)
        {
            GetComponent<SpriteAnimator>()->Play(ANIM_CHARGE_LOOP);
            isChargeLoop = true;
        }
    }

    // 計算用変数
    hft::HFFLOAT2 aimVector = { 0, 0 }; // 狙っている方向ベクトル(矢印用)
    bool isReleased = false;           // 発射判定
    bool isCanceled = false;           // キャンセル判定

    // ===================================================
    // マウス操作
    // ===================================================
    if (mouseMode)
    {
        float mx = (float)pInput->GetMouseCenterX();
        float my = (float)pInput->GetMouseCenterY();

        float pullX = dragStartPos.x - mx;
        float pullY = dragStartPos.y - my;
        float mag = std::sqrt(pullX * pullX + pullY * pullY);

        aimVector = { pullX, pullY };

        // --- パワー計算 ---

        const float MAX_DRAG_DIST = 200.0f;

        float basePower = (mag / MAX_DRAG_DIST) * limit_hammer_power;

        if (basePower > limit_hammer_power) basePower = limit_hammer_power;

        if (basePower >= limit_hammer_power * 0.9f)
        {
            chargeTimer++;
            float bonusPower = chargeTimer * charge_speed;

            // 基本(20) + ボーナス で計算
            hammer_power = basePower + bonusPower;
        }
        else
        {
            chargeTimer = 0;
            hammer_power = basePower;
        }

        // マウス判定
        if (pInput->GetMouseRelease(Button::Mouse::Left))
        {
            if (hammer_power < 1.0f) isCanceled = true;
            else isReleased = true;
        }
    }
    // ===================================================
    // コントローラー操作
    // ===================================================
    else
    {
        hft::HFFLOAT2 stick = pInput->GetLeftAnalogStick();
        float mag = std::sqrt(stick.x * stick.x + stick.y * stick.y);

        aimVector = { -stick.x, stick.y };

        // --- パワー計算 ---

        float normalizedMag = 0.0f;

        if (mag > CHARGE_THRESHOLD)
        {
            // (現在の傾き - 閾値) / (1.0 - 閾値)
            normalizedMag = (mag - CHARGE_THRESHOLD) / (1.0f - CHARGE_THRESHOLD);
        }

        // 正規化した値を使って目標パワーを計算
        float targetPower = normalizedMag * limit_hammer_power;

        // 限界まで倒している時だけ、さらにボーナスを加算する（限界突破）
        if (mag > 0.9f)
        {
            chargeTimer++;
            float bonusPower = chargeTimer * charge_speed;
            targetPower += bonusPower;
        }
        else
        {
            chargeTimer = 0;
        }

        // 現在のパワーを、目標パワーに向けて徐々に変化させる
        if (hammer_power < targetPower)
        {
            hammer_power += charge_speed;

            // 行き過ぎ防止（目標を超えたら合わせる）
            if (hammer_power > targetPower) hammer_power = targetPower;
        }
        else
        {
            hammer_power = targetPower;

        }

        // 判定
        if (mag < CHARGE_THRESHOLD) isCanceled = true;
        if (!pInput->GetButtonPress(Button::XBox::X))
        {
            if (hammer_power < 1.0f)
            {
                isCanceled = true;
            }
            else
            {
                isReleased = true;
            }
        }
    }

    // 方向保存処理
    if (std::abs(aimVector.x) > std::abs(aimVector.y)) {
        attackDirection.x = (aimVector.x > 0) ? -1.0f : 1.0f;
        attackDirection.y = 0.0f;
    }
    else {
        attackDirection.x = 0.0f;
        attackDirection.y = (aimVector.y > 0) ? -1.0f : 1.0f;
    }

    // ===================================================
    // 共通処理
    // ===================================================

    if (hammer_power > max_hammer_power) hammer_power = max_hammer_power;

    // キャンセル処理
    if (isCanceled)
    {
        chargeTimer = 0;
        hammer_power = 0.0f;
        ChangeState(PLAYER_STATE::SELECT);
        if (pArrow) pArrow->Hide();
        std::cout << "Action: Canceled" << std::endl;
        return;
    }

    // 発射処理
    if (isReleased)
    {
        ChangeState(PLAYER_STATE::RELEASE);
        std::cout << "STATE: Charge >> Release" << std::endl;
        return;
    }

    // 矢印表示
    if (pArrow && pTuningFork)
    {
        float shotAngle = 0.0f;

        // aimVector から角度(90度刻み)を算出
        if (std::abs(aimVector.x) > std::abs(aimVector.y)) {
            shotAngle = (aimVector.x > 0) ? 0.0f : 180.0f;
        }
        else {
            shotAngle = (aimVector.y > 0) ? 270.0f : 90.0f;
        }

        // 後ろ向き判定
        float angleDiff = std::abs(shotAngle - this->angle.x);
        if (angleDiff > 180.0f) angleDiff = 360.0f - angleDiff;

        if (angleDiff < 1.0f || hammer_power < 1.0f)
        {
            pArrow->Hide();
            //hammer_power = 0.0f;
            chargeTimer = 0;
        }
        else
        {
            // パワー比率 (0.0 ～ 1.0)
            float ratio = hammer_power / max_hammer_power;

            float shakeAngle = 0.0f;

            // パワーが半分(0.5)を超えたら震え始める
            if (ratio > 0.5f)
            {
                // 震えの強さ係数 (0.5を超えた分だけ強くなる)
                // 最大パワー時で 1.0 になる計算: (1.0 - 0.5) * 2 = 1.0
                float shakeStrength = (ratio - 0.5f) * 2.0f;

                // ランダムなノイズ (-1.0 ～ 1.0) を生成
                float noise = (float)(rand() % 200 - 100) / 100.0f;

                // ブレさせる
                shakeAngle = noise * 1.5f * shakeStrength;
            }


            hft::HFFLOAT2 targetPos = {
                pTuningFork->GetTransformPtr()->position.x,
                pTuningFork->GetTransformPtr()->position.y
            };

            pArrow->UpdateTransform(targetPos, shotAngle + shakeAngle, ratio);
            pArrow->GetTransformPtr()->position.z = -11;
        }
    }

    int currentAngle = (int)(angle.x + 0.5f) % 360;
    // 右を向いている時 (0度)
    if (currentAngle == 0)
    {
		if (p_transform->scale.x < 0) p_transform->scale.x *= -1; // 右向きに補正
    }
    // 左を向いている時 (180度)
    else if (currentAngle == 180)
    {
		if (p_transform->scale.x > 0) p_transform->scale.x *= -1; // 左向きに補正
    }
}

void PlayerObject::UpdateRelease()
{
    animTimer++;

    // ---------------------------------------------------
    // 1フレーム目：アニメ開始
    // ---------------------------------------------------
    if (animTimer == 1)
    {
        hft::HFFLOAT2 moveVec = attackDirection;
        hft::HFFLOAT2 faceDir = GetVecFromAngle(angle.x);

        // バックステップ（真後ろ）判定
        if (moveVec.x == -faceDir.x && moveVec.y == -faceDir.y)
        {
            // キャンセル処理...
            ChangeState(PLAYER_STATE::STAND);
            if (pTuningFork) pTuningFork->Hide();
            if (pArrow) pArrow->Hide();
            hammer_power = 0.0f;
            return;
        }

        auto animator = GetComponent<SpriteAnimator>();

        // 今の向きを整数(0, 90, 180, 270)で取得して扱いやすくする
        int currentAngle = (int)(angle.x + 0.5f) % 360;

        // 右を向いている時 (0度)
        if (currentAngle == 0)
        {
            if (moveVec.x > 0.5f)       animator->Play(ANIM_ATTACK_FRONT); // 右(正面)
            else if (moveVec.y < -0.5f) animator->Play(ANIM_ATTACK_LEFT); // 上
            else if (moveVec.y > 0.5f) {
				p_transform->scale.x *= -1; // 左右反転
                animator->Play(ANIM_ATTACK_RIGHT); // 下
            }
        }
        // 上を向いている時 (90度)
        else if (currentAngle == 90)
        {
            if (moveVec.y < -0.5f)      animator->Play(ANIM_ATTACK_LEFT); // 上(正面)
            else if (moveVec.x < -0.5f) animator->Play(ANIM_ATTACK_LEFT); // 左
            else if (moveVec.x > 0.5f) {
                p_transform->scale.x *= -1; //左右反転
                animator->Play(ANIM_ATTACK_LEFT); // 右
            }
        }
        // 左を向いている時 (180度)
        else if (currentAngle == 180)
        {
            if (p_transform->scale.x > 0) p_transform->scale.x *= -1; // 左向きに補正
            if (moveVec.x < -0.5f)      animator->Play(ANIM_ATTACK_FRONT); // 左(正面)
            else if (moveVec.y > 0.5f) {
				p_transform->scale.x *= -1; // 左右反転
                animator->Play(ANIM_ATTACK_RIGHT); // 下
            }
            else if (moveVec.y < -0.5f) animator->Play(ANIM_ATTACK_LEFT); // 上
        }
        // 下を向いている時 (270度)
        else if (currentAngle == 270)
        {
            if (moveVec.y > 0.5f)       animator->Play(ANIM_ATTACK_RIGHT); // 下(正面)
            else if (moveVec.x > 0.5f)  animator->Play(ANIM_ATTACK_FRONT); // 右
            else if (moveVec.x < -0.5f) {
				p_transform->scale.x *= -1; // 左右反転
                animator->Play(ANIM_ATTACK_FRONT); // 左
            }
        }

        if (pTuningFork) pTuningFork->Hide();
        if (pArrow) pArrow->Hide();
    }

    // ---------------------------------------------------
    // 攻撃実行タイミング
    // ---------------------------------------------------
    if (animTimer == SLIDE_START_TIMING)
    {
        hft::HFFLOAT2 moveVec = attackDirection;

        if (pMap)
        {
            hft::HFFLOAT2 anchorIdx = GetTargetIndex();
            try
            {
                if (anchorIdx.x >= 0 && anchorIdx.y >= 0) {
                    pMap->SetSlideData(anchorIdx, moveVec, hammer_power);
                    if (pTuningFork) pTuningFork->PlayHitEffect();

                    float ratio = hammer_power / max_hammer_power;

                    int playId = -1;

                    if (ratio >= 0.8f)
                    {
                        playId = SE_LAttack; // 強 (80% ～ 100%)
                    }
                    else if (ratio >= 0.4f)
                    {
                        playId = SE_MAttack;    // 中 (40% ～ 79%)
                    }
                    else
                    {
                        playId = SE_SAttack;   // 弱 (0% ～ 39%)
                    }

                    if (playId != -1)
                    {
                        SoundManager::GetInstance().Play(playId);
                    }

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
    if (animTimer > SLIDE_END_TIMING)
    {
        ChangeState(PLAYER_STATE::STAND);
    }
}

void PlayerObject::UpdateDamage()
{
    animTimer++; // アニメーション時間を進める

    // HITアニメは7コマ×4フレーム = 28フレームなので、30くらいで復帰
    if (animTimer > 30)
        ChangeState(PLAYER_STATE::STAND);

    std::cout << "STATE:Hit >> Stand" << std::endl;
}

void PlayerObject::UpdateDead()
{
    auto animator = GetComponent<SpriteAnimator>();

    if (animTimer + 1 >= DEAD_ANIM_END)
    {
        animator->Play(ANIM_DEAD_LOOP);
    }
    else
        animTimer++;
}

void PlayerObject::OnHit()
{
	if (invincible || state == PLAYER_STATE::DEAD) return; // 無敵中や死亡中は無視

    if (pArrow) pArrow->Hide();

    hitpoint--;
    std::cout << "Player Damaged! HP:" << hitpoint << std::endl;

    if (hitpoint <= 0)
    {
        OnDead();
    }
    else
    {
        invincible = true;
		inv_cnt = inv_time;

        // ステート変更
        ChangeState(PLAYER_STATE::HIT);
        SoundManager::GetInstance().Play(SE_Hit);
        std::cout << "STATE: PlayerHit" << std::endl;
    }
}

void PlayerObject::OnDead()
{
    ChangeState(PLAYER_STATE::DEAD);
    SoundManager::GetInstance().Play(SE_Dead);
    std::cout << "STATE: PlayerDEAD" << std::endl;

    isDead = true;
	std::cout << "Player_isDead:" << isDead << std::endl;

    // ここにゲームオーバー処理などを追加
}

void PlayerObject::OnCollisionEnter(Collider* _p_col)
{
    // 無敵中や死亡中は無視
    if (invincible || state == PLAYER_STATE::DEAD) return;

    // 相手のタグを取得
    std::string tag = _p_col->GetGameObject()->GetTag();

    // 敵やダメージ床に触れたら OnHit を呼ぶ
    if (tag == "Enemy" || tag == "DamageObject" || tag == "Connect")
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
		animator->Stop(ANIM_CHARGE_LOOP);
        break;

    case PLAYER_STATE::HIT:
        animator->Stop(ANIM_HIT);
        break;

    case PLAYER_STATE::RELEASE:
        animator->Stop(ANIM_ATTACK_FRONT);
		animator->Stop(ANIM_ATTACK_RIGHT);
		animator->Stop(ANIM_ATTACK_LEFT);
        break;

    case PLAYER_STATE::DEAD:
        animator->Stop(ANIM_DEAD);
        break;
    }

    // SELECT -> CHARGE (設置開始)
    if (state == PLAYER_STATE::SELECT && _nextState == PLAYER_STATE::CHARGE)
    {
        if (pTuningFork)
        {
            // 設置する座標を計算 (現在のSelectカーソル位置)
            hft::HFFLOAT2 myPos = { p_transform->position.x, p_transform->position.y };
            hft::HFFLOAT2 dirVec = GetVecFromAngle(angle.x);
            hft::HFFLOAT2 targetPos = {
                 myPos.x + (dirVec.x * tileSize),
                 myPos.y - (dirVec.y * tileSize)
            };

            // アニメーション再生！
            pTuningFork->PlayAppear(targetPos);
        }
    }
    // CHARGE -> SELECT/STAND (キャンセル/中断)
    else if (state == PLAYER_STATE::CHARGE && _nextState != PLAYER_STATE::RELEASE)
    {
        // 攻撃発射(RELEASE)以外でチャージを抜けるときは、音叉を片付ける
        if (pTuningFork)
        {
            pTuningFork->PlayDisappear();
        }
    }

    state = _nextState; //ステート更新
    animTimer = 0;
    isChargeLoop = false;

	chargeTimer = 0; // チャージタイマーリセット

	p_transform->rotation.z = 0.0f; // 傾きをリセット
	if (p_transform->scale.x < 0.0f) p_transform->scale.x *= -1; // 左右反転をリセット

    //次ステートのアニメーション再生
    switch (state) {
    case PLAYER_STATE::STAND:   animator->Play(ANIM_STAND); break;
    case PLAYER_STATE::CHARGE:  animator->Play(ANIM_CHARGE); break;
    case PLAYER_STATE::HIT:     animator->Play(ANIM_HIT); break;
    case PLAYER_STATE::DEAD:    animator->Play(ANIM_DEAD); break;
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