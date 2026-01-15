#include "UIManager.h"

//タイトルシーンの処理=======================================================
void TitleUIManager::Init()
{
	backGround.Init({ 0.f, 0.f, 0.f }, { 500.f, 500.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::NormalType);

	titleUI.Init({ 0.f, 200.f, -1.f }, { 500.f, 100.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::NormalType);

	gameStartButton.Init({ 0.f, -100.f, -1.f }, { 200.f, 50.f }, "Assets/01-Texture/99-Test/wave.png", Type_UI::ButtonType);
	gameStartButton.SetTargetKey(Button::KeyBord::A);
	gameStartButton.SetTargetXBoxButton(Button::XBox::A);

	gameEndButton.Init({ 0.f, -150.f, -1.f }, { 200.f, 50.f }, "Assets/01-Texture/99-Test/wave.png", Type_UI::ButtonType);
	gameEndButton.SetTargetKey(Button::KeyBord::B);
	gameEndButton.SetTargetXBoxButton(Button::XBox::B);

	sceneTransitionUI.Init({ 600.f, 0.f, -3.f }, { 500.f, 500.f }, "Assets/01-Texture/99-Test/field.jpg", Type_UI::NormalType);

}

void TitleUIManager::Update()
{
	if (GetIsPressedStartButton())
	{
		startTransitionAnim = true;
	}


	if (GetIsPressedEndButton())
	{

	}


	//ゲームスタートボタンを押した時のアニメーション
	if (startTransitionAnim)
	{
		SceneTransitionAnim();
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

void TitleUIManager::SceneTransitionAnim()
{
	Transform* tfm = sceneTransitionUI.GetTransformPtr();
	hft::HFFLOAT3 pos = tfm->position;
	

	tfm->position.x -= 10.f;

	if (tfm->position.x <= 0.f)
	{
		tfm->position.x = 0.f;
	}
}



//ステージセレクトシーンの処理=======================================================

void StagePlayUIManager::Init()
{
	//ポーズボタンUI
	poseButton.Init({ -400.f, 200.f, 0.f }, { 80.f, 80.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::ButtonType);
	poseButton.SetTargetKey(Button::KeyBord::Escape);
	poseButton.SetTargetXBoxButton(Button::XBox::X);


	//リトライボタンUI
	retryButton.Init({ -400.f, 100.f, 0.f }, { 80.f, 80.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::ButtonType);
	retryButton.SetTargetKey(Button::KeyBord::Escape);
	retryButton.SetTargetXBoxButton(Button::XBox::X);


	//プレイヤーのHPバーのUI
	playerHpBar.Init({ 400.f, -100.f, 0.f }, { 100.f, 400.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::NormalType);


	//ポーズボタンが押された時のUI
	poseBackGround.Init({ 0.f, 0.f, 1.f }, { 150.f, 500.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::NormalType);
	
	restartButton.Init({ 0.f, 100.f, 0.f }, { 80.f, 50.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::ButtonType);
	restartButton.SetTargetKey(Button::KeyBord::A);
	restartButton.SetTargetXBoxButton(Button::XBox::A);

	goStageSelectButton.Init({ 0.f, 0.f, 0.f }, { 80.f, 50.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::ButtonType);
	goStageSelectButton.SetTargetKey(Button::KeyBord::A);
	goStageSelectButton.SetTargetXBoxButton(Button::XBox::A);

	goTitleButton.Init({ 0.f, -100.f, 0.f }, { 80.f, 50.f }, "Assets/01-Texture/99-Test/daruma.jpg", Type_UI::ButtonType);
	goTitleButton.SetTargetKey(Button::KeyBord::A);
	goTitleButton.SetTargetXBoxButton(Button::XBox::A);
}


void StagePlayUIManager::Update()
{
	//ポーズボタンを押したときの処理
	if (!isPose && poseButton.GetIsPressed())
	{
		isPose = true;
	}

	//フラグごとのUIの状態変化
	if (isPose)
	{
		PoseMode();
		return;
	}
	
	if (isGoStageSelect)
	{
		GoStageSelectMode();
		return;
	}

	if (isGoTitle)
	{
		GoTitleMode();
		return;
	}

	if (isGameOver)
	{
		GameOverMode();
		return;
	}

	if (isStageClear)
	{
		StageClearMode();
		return;
	}

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
		isPose    = false;
		isGoTitle = true;
		return;
	}
}

void StagePlayUIManager::GoTitleMode()
{

}

void StagePlayUIManager::GoStageSelectMode()
{

}

void StagePlayUIManager::GameOverMode()
{

}

void StagePlayUIManager::StageClearMode()
{

}

void StagePlayUIManager::PlayMode()
{
	poseBackGround.SetIsRender(false);
	restartButton.SetIsRender(false);
	goStageSelectButton.SetIsRender(false);
	goTitleButton.SetIsRender(false);
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
