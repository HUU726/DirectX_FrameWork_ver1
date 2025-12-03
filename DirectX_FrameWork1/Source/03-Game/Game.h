#pragma once


/**
* @file		ゲームクラスを作る
* @date		2025/05/22
*/

#include <Windows.h>


class Game
{
private:

	Game();

public:
	~Game();
	static Game& GetInstance()
	{
		static Game instance;
		return instance;
	}

	void Init();	//初期化
	void Uninit();	//終了処理
	void Run();		//ゲームループ
};