#pragma once


/**
* @brief	ゲームクラスを作る
* @date		2025/05/22
*/

#include <Windows.h>


class Game
{
private:

	void Update();				//更新
	void Draw();				//描画
	Game();

public:
	~Game();
	static Game& GetInstance()
	{
		static Game instance;
		return instance;
	}

	void Init();	//初期化
	void Run();		//実行
	void Uninit();	//終了処理

};