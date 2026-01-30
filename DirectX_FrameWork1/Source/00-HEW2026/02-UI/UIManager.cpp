#include "UIManager.h"

#include "../../99-Lib/01-MyLib/06-GameObject/999-GameObjectManager/GameObjectManager.h"
#include "../../00-HEW2026/01-GamaeObject/01-TrackObject/04-Player/PlayerObject.h"

#include "../../99-Lib/01-MyLib/03-Sound/Fsound.h"

#include "../../02-App/Application.h"
#include "../../02-App/HF_Window.h"

//タイトルシーン管理の処理=======================================================
void TitleUIManager::Init()
{
	{	//背景
		hft::HFFLOAT2 windowSize = Application::GetInstance().GetWindowSize();
		backGround.Init({ 0.f, 0.f, 0.f }, windowSize, "Assets/01-Texture/20-BGImg/01-Title/title1.png", Type_UI::NormalType);
	}

	{	//ボタン

		hft::HFFLOAT3 basePos = { -155,-125,-1 };
		hft::HFFLOAT3 buttonScl = { 500,125,1 };

		gameStartButton.Init(basePos, buttonScl, "Assets/01-Texture/10-UI/10-Title/Button_Start.png", Type_UI::ButtonType);
		gameStartButton.SetTargetKey(Button::KeyBord::A);
		gameStartButton.SetTargetXBoxButton(Button::XBox::A);

		basePos.y -= buttonScl.y * 1.3f;
		gameEndButton.Init(basePos, buttonScl, "Assets/01-Texture/10-UI/10-Title/Button_End.png", Type_UI::ButtonType);
		gameEndButton.SetTargetKey(Button::KeyBord::B);
		gameEndButton.SetTargetXBoxButton(Button::XBox::B);

	}


	int bgmID = SoundManager::GetInstance().AddSoundDirect("Assets/03-Sound/20-BGM/Title.wav", true, true);
	SoundManager::GetInstance().SetVolume(bgmID, 0.3f);
}

#include "../../99-Lib/01-MyLib/08-Scene/02-SceneManager/SceneManager.h"
#include "../20-Scene/02_StageSelectScene.h"
void TitleUIManager::Update()
{
	if (GetIsPressedStartButton())
	{
		SceneManager::GetInstance().LoadScene<Hew_StageSelectScene>();
	}


	if (GetIsPressedEndButton())
	{
		Application::GetInstance().GetWindowPtr()->EndWindow();
	}

}

bool TitleUIManager::GetIsPressedStartButton()
{
	return gameStartButton.GetIsPressed();
}

bool TitleUIManager::GetIsPressedEndButton()
{
	return gameEndButton.GetIsPressed();
}


//ステージプレイシーン管理の処理=======================================================
void StagePlayUIManager::Init()
{
	//ポーズボタンUI
	{
		poseButton.Init({ -700.f, 400.f, -95.f }, { 350.f, 150.f }, "Assets/01-Texture/10-UI/12-Game/UI_PlayView_Pause.png", Type_UI::ButtonType);
		poseButton.SetTargetKey(Button::KeyBord::Tab);
		poseButton.SetTargetXBoxButton(Button::XBox::X);
	}


	//リトライボタンUI
	{
		retryButton.Init({ -700.f, 170.f, -95.f }, { 350.f, 150.f }, "Assets/01-Texture/10-UI/12-Game/UI_PlayView_Retry.png", Type_UI::ButtonType);
		retryButton.SetTargetKey(Button::KeyBord::R);
		retryButton.SetTargetXBoxButton(Button::XBox::X);
	}


	//プレイヤーのHPバーのUI
	{
		playerHpBar.Init({ 450.f, -100.f, -95.f }, { 100.f, 400.f }, "Assets/01-Texture/10-UI/01-HP/HP_Middle.png", Type_UI::NormalType);

		playerHpBarFront.Init({ 450.f, -100.f, -96.f }, { 100.f, 400.f }, "Assets/01-Texture/10-UI/01-HP/HP_Front.png", Type_UI::NormalType);

		//プレイヤーのHPバー背景UI
		playerHpBarBack.Init({ 450.f, -100.f, -94.f }, { 100.f, 400.f }, "Assets/01-Texture/10-UI/01-HP/HP_Back.png", Type_UI::NormalType);

		//barの最大Yサイズと初期Y位置を設定
		maxHpBerHeight = 400.f;
		barInitialPosY = -100.f;
	}


	//ポーズボタンが押された時のUI
	{
		poseBackGround.Init({ -80.f, 0.f, -98.f }, { 800.f, 850.f }, "Assets/01-Texture/10-UI/12-Game/UI_PlayView_Pausemenu_paper.png", Type_UI::NormalType);

		restartButton.Init({ 0.f, 150.f, -98.f }, { 600.f, 250.f }, "Assets/01-Texture/10-UI/12-Game/UI_PlayView_Pausemenu_restart.png", Type_UI::ButtonType);
		restartButton.SetTargetKey(Button::KeyBord::A);
		restartButton.SetTargetXBoxButton(Button::XBox::A);

		goStageSelectButton.Init({ 0.f, 0.f, -98.f }, { 500.f, 200.f }, "Assets/01-Texture/10-UI/12-Game/UI_PlayView_Pausemenu_select.png", Type_UI::ButtonType);
		goStageSelectButton.SetTargetKey(Button::KeyBord::A);
		goStageSelectButton.SetTargetXBoxButton(Button::XBox::A);

		goTitleButton.Init({ 0.f, -150.f, -98.f }, { 500.f, 200.f }, "Assets/01-Texture/10-UI/12-Game/UI_PlayView_Pausemenu_title.png", Type_UI::ButtonType);
		goTitleButton.SetTargetKey(Button::KeyBord::A);
		goTitleButton.SetTargetXBoxButton(Button::XBox::A);
	}


	//ゲームオーバー時のUI
	{
		gameOverUI.Init({ 0.f, 200.f, -99.f }, { 200.f, 100.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::NormalType);
		gameOverUI.SetIsRender(false);


		//リトライボタン
		gameOverRetryButton.Init({ 0.f, -50.f, -99.f }, { 200.f, 100.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::ButtonType);
		gameOverRetryButton.SetTargetKey(Button::KeyBord::B);
		gameOverRetryButton.SetTargetXBoxButton(Button::XBox::B);
		gameOverRetryButton.SetIsRender(false);


		//ステージセレクトに行くボタン
		gameOverStageSelectButton.Init({ 0.f, -200.f, -99.f }, { 200.f, 100.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::ButtonType);
		gameOverStageSelectButton.SetTargetKey(Button::KeyBord::B);
		gameOverStageSelectButton.SetTargetXBoxButton(Button::XBox::B);
		gameOverStageSelectButton.SetIsRender(false);
	}


	//ステージクリア
	{
		clearUI.Init({ 0.f, 0.f, -99.f }, { 200.f, 100.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::NormalType);
		clearUI.SetIsRender(false);
	}
}


void StagePlayUIManager::Update()
{
	//フラグごとのUIの状態変化
	if (isRetry) { RetryMode(); return; }

	if (isGoStageSelect) { GoStageSelectMode(); return; }

	if (isGoTitle) { GoTitleMode(); return; }

	if (isGameOver) { GameOverMode(); return; }

	if (isStageClear) { StageClearMode(); return; }

	if (isPose) { PoseMode(); return; }

	PlayMode();
}


void StagePlayUIManager::PoseMode()
{
	poseBackGround.SetIsRender(true);
	restartButton.SetIsRender(true);
	goStageSelectButton.SetIsRender(true);
	goTitleButton.SetIsRender(true);

	if (restartButton.GetIsPressed())
	{
		isPose = false;
		return;
	}

	if (goStageSelectButton.GetIsPressed())
	{
		isPose = false;
		isGoStageSelect = true;
		return;
	}

	if (goTitleButton.GetIsPressed())
	{
		isPose = false;
		isGoTitle = true;
		return;
	}
}

#include "../20-Scene/01_Hew_TitleScene.h"
void StagePlayUIManager::GoTitleMode()
{
	SceneManager::GetInstance().LoadScene<Hew_TitleScene>();
}

#include "../20-Scene/02_StageSelectScene.h"
void StagePlayUIManager::GoStageSelectMode()
{
	SceneManager::GetInstance().LoadScene<Hew_StageSelectScene>();
}

void StagePlayUIManager::GameOverMode()
{
	gameOverUI.SetIsRender(true);
	gameOverRetryButton.SetIsRender(true);
	gameOverStageSelectButton.SetIsRender(true);

	if (gameOverRetryButton.GetIsPressed())
	{
		isRetry = true;
		isGameOver = false;
		return;
	}

	if (gameOverStageSelectButton.GetIsPressed())
	{
		isGoStageSelect = true;
		isGameOver = false;
		return;
	}
}


void StagePlayUIManager::StageClearMode()
{
	clearUI.SetIsRender(true);

	return;
}

#include "../20-Scene/03_GameScene.h"
void StagePlayUIManager::RetryMode()
{
	SceneManager::GetInstance().LoadScene<Hew_GameScene>();
	return;
}

void StagePlayUIManager::PlayMode()
{
	//ポーズ時のUIを非表示
	poseBackGround.SetIsRender(false);

	restartButton.SetIsActive(false);
	restartButton.SetIsRender(false);

	goStageSelectButton.SetIsRender(false);
	goStageSelectButton.SetIsRender(false);

	goTitleButton.SetIsActive(false);
	goTitleButton.SetIsRender(false);


	//プレイヤーのHPバーの長さを切り替え
	ScalePlayerHPBer();


	//ポーズボタンを押したときはポーズモードに移行
	if (!isPose && poseButton.GetIsPressed())
	{
		isPose = true;
		return;
	}

	//HPが0以下になったらゲームオーバーモードに移行
	if (playerCurHp <= 0)
	{
		isGameOver = true;
		return;
	}

	if (enemyCount <= 0)
	{
		isStageClear = true;
		return;
	}


}


void StagePlayUIManager::ScalePlayerHPBer()
{
	//プレイヤータグのついたオブジェクトを参照し、HPバーの大きさを調整する
	std::vector<GameObject*> playerObjArray = GameObjectManager::GetInstance().FindGameObject_Tag("Player");

	if (playerObjArray.empty()) { return; }

	PlayerObject* player = dynamic_cast<PlayerObject*>(playerObjArray[0]);

	if (player == nullptr) { return; }

	playerCurHp = player->GetPlayerHP();
	playerMaxHp = player->GetPlayerMaxHP();


	float hpRatio = (float)playerCurHp / playerMaxHp;
	float currentScaleY = maxHpBerHeight * hpRatio;

	float moveValue = -1 * (maxHpBerHeight - currentScaleY) / 2;
	float currentPosY = barInitialPosY + moveValue;

	playerHpBar.GetTransformPtr()->scale.y = currentScaleY;
	playerHpBar.GetTransformPtr()->position.y = currentPosY;
}

void StagePlayUIManager::SetPlayerData()
{
}

bool StagePlayUIManager::GetIsPose()
{
	return isPose;
}

bool StagePlayUIManager::GetIsGameOver()
{
	return isGameOver;
}

bool StagePlayUIManager::GetIsStageClear()
{
	return isStageClear;
}

bool StagePlayUIManager::GetIsGoStageSelect()
{
	return isGoStageSelect;
}

bool StagePlayUIManager::GetIsGoTitle()
{
	return isGoTitle;
}

bool StagePlayUIManager::GetIsRetry()
{
	return isRetry;
}