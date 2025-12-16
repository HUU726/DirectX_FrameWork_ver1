#pragma once

#include <vector>


class GameObject;

class GameObjectManager
{
private:
	int idCnt;								//生成されたオブジェクト総数
	std::vector<GameObject*> gameObjects;	//現在生成中のGameObject格納コンテナ
	std::vector<GameObject*> waitingQueue;	//次シーンのオブジェクトを待機させておくコンテナ

	GameObjectManager() : idCnt(0) {}

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

	/**
	* @brief	実際に使うコンテナに待機コンテナをスワップ
	*/
	void SetUpObject();
	/**
	* @brief	コンテナ内オブジェクトを削除
	*/
	void Clear();

	/**
	* @brief	格納済みゲームオブジェクトのUpdate関数を呼び出す
	* @note		UnityでいうScriptにあたる
	*/
	void Action();

};

