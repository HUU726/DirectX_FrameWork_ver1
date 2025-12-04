#pragma once

#include <vector>


class GameObject;

class GameObjectManager
{
private:
	int idCnt;								//生成されたオブジェクト総数
	std::vector<GameObject*> gameObjects;	//現在生成中のGameObject格納コンテナ

	GameObjectManager() {}

public:
	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}

	/**
	* @brief	ゲームオブジェクト追加
	* @param	GameObject*		_p_gameObject	ゲームオブジェクトポインタ
	*/
	void AddGameObject(GameObject* _p_gameObject);
	/**
	* @brief	ゲームオブジェクト削除
	* @param	GameObject*		_p_gameObject	ゲームオブジェクトポインタ
	*/
	void RemoveGameObject(GameObject* _p_gameObject);
	void Clear();

	/**
	* @brief	格納済みゲームオブジェクトのUpdate関数を呼び出す
	* @note		UnityでいうScriptにあたる
	*/
	void Action();

};

