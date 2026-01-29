#pragma once

#include "UI.h"










//ステージセレクトシーンのUI管理
class StageSelectUIManager : public GameObject2D
{
private:
	GameObject* pLogic;

	bool isStartStage = false;		//ステージ開始しているかどうか
	bool isGoTitle = false;			//タイトル移行状態かどうか

public:
	~StageSelectUIManager();
	void Init() override;
	void Update() override;
};