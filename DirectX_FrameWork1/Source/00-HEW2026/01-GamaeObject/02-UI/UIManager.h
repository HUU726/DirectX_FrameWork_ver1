#pragma once
#include "../../../99-Lib/01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"

#include"../../../04-Input/Input.h"

#include "UI.h"

//タイトルシーンのUI管理
class TitleUIManager : public GameObject2D
{
private:
	UI backGround;
	UI titleUI;
	UI gameStartButton;
	UI gameEndButton;
	UI sceneTransitionUI;

	//シーン遷移のアニメーションをするか否か
	bool startTransitionAnim = false;

public:
	void Init() override;
	void Update() override;

	bool GetIsPressedStartButton(); //ゲームスタートボタンが押されたか検知
	bool GetIsPressedEndButton();   //ゲーム終了ボタンが押されたか検知

	//シーン遷移用UIの座標を変化させてアニメーション
	void SceneTransitionAnim();
};


//ステージセレクトシーンのUI管理
class StageSelectUIManager : public GameObject2D
{
	UI backGround;
	UI stageTitleUI;
	UI stageStartButton;
	UI goToTitleButton;

};



//ステージプレイシーンの管理
class StagePlayUIManager : public GameObject2D
{
private:
	UI poseButton;
	UI retryButton;
	UI playerHpBar;


	UI poseBackGround;
	UI restartButton;
	UI goStageSelectButton;
	UI goTitleButton;

	bool isPose		     = false;
	bool isGoStageSelect = false;
	bool isGoTitle		 = false;
	bool isGameOver      = false;
	bool isStageClear    = false;
public:
	void Init() override;
	void Update() override;

	void PoseMode();
	void GoTitleMode();
	void GoStageSelectMode();
	void GameOverMode();
	void StageClearMode();
	void PlayMode();


	bool GetIsPose();
	bool GetIsGameOver();
	bool GetIsStageClear();
};