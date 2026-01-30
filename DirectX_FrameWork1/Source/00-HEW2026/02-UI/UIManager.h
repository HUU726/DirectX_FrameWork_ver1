#pragma once

#include <array>

#include "../../99-Lib/01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"

#include "../../04-Input/Input.h"

#include "UI.h"

//タイトルシーンのUI管理
class TitleUIManager : public GameObject2D
{
private:
	UI backGround;
	UI gameStartButton;
	UI gameEndButton;

	//シーン遷移のアニメーションをするか否か
	bool startTransitionAnim = false;

public:
	void Init() override;
	void Update() override;

	//ゲームスタートボタンが押されたか検知
	bool GetIsPressedStartButton();

	//ゲーム終了ボタンが押されたか検知
	bool GetIsPressedEndButton();

};







//ステージプレイシーンの管理
class StagePlayUIManager : public GameObject2D
{
private:
	UI poseButton;
	UI retryButton;
	UI playerHpBar;
	UI playerHpBarFront;
	UI playerHpBarBack;

	UI poseBackGround;
	UI restartButton;
	UI goStageSelectButton;
	UI goTitleButton;

	UI gameOverUI;					//ゲームオーバー時のUI
	UI gameOverRetryButton;			//ゲームオーバー後のリトライボタン
	UI gameOverStageSelectButton;	//ゲームオーバー後のステージセレクトボタン

	//UI clearUI;
	UI clearStageSelectButton;
	UI clearTitleButton;
	std::array<UI, 10> clearLogos;

	int clearAnimTimer = 0;

	//ゲームオーバーUIの最大サイズ
	hft::HFFLOAT2 maxSize = { 200.f, 100.f };
	float scaleUpSpeed = 10.f;

	float maxHpBerHeight; //バーの最大サイズ
	float barInitialPosY; //barの初期Y位置

	//プレイヤーのHP
	int playerMaxHp = 3;	//最大HP
	int playerCurHp = 3;	//現在のHP

	//敵のカウンター(仮)
	int enemyCount = 3;

	//各状態のフラグ
	bool isPose = false;
	bool isGoStageSelect = false;
	bool isGoTitle = false;
	bool isGameOver = false;
	bool isStageClear = false;
	bool isRetry = false;
public:
	void Init() override;
	void Update() override;


	//ポーズ状態の処理
	void PoseMode();

	//タイトルシーンに移行時の処理
	void GoTitleMode();

	//ステージセレクトに移行時の処理
	void GoStageSelectMode();

	//ゲームオーバー時の処理
	void GameOverMode();

	//ステージクリア時の処理
	void StageClearMode();

	//ステージやり直しの時の処理
	void RetryMode();

	//通常プレイ時の処理
	void PlayMode();

	void ScalePlayerHPBer(); //プレイヤーのHPバーの伸縮
	void SetPlayerData();


	//各状態フラグのゲッター
	bool GetIsPose();
	bool GetIsGameOver();
	bool GetIsStageClear();
	bool GetIsGoStageSelect();
	bool GetIsGoTitle();
	bool GetIsRetry();
};