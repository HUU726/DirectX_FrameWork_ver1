#pragma once

#include <vector>
#include <string>


class GameObject;

class GameObjectManager
{
private:
	int idCnt;								//生成されたオブジェクト総数
	std::vector<GameObject*> gameObjects;	//現在生成中のGameObject格納コンテナ
	std::vector<GameObject*> waitingQueue;	//次シーンのオブジェクトを待機させておくコンテナ
	std::vector<GameObject*> destroyQueue;	//削除オブジェクト格納コンテナ

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
	* @brief	ゲームオブジェクトを消去
	* @param	GameObject*		_p_gameObject	ゲームオブジェクトポインタ
	*/
	void DestroyGameObject(GameObject* _p_gameObject);

	/**
	* @brief	実際に使うコンテナに待機コンテナをスワップ
	*/
	void SetUpObject();
	/**
	* @brief	コンテナ内オブジェクトを削除
	*/
	void Clear();
	/**
	* @brief	待機コンテナを空にする
	*/
	void ClearWaitingQueue();
	/**
	* @brief	削除オブジェクトコンテナ内のオブジェクトを解放
	*/
	void ClearDestroyQueue();
	/**
	* @brief	待機コンテナの中身を現在コンテナに追加する
	*/
	void AddWaitToNow();

	/**
	* @brief	格納済みゲームオブジェクトのUpdate関数を呼び出す
	* @note		UnityでいうScriptにあたる
	*/
	void Action();


	std::vector<GameObject*> FindGameObject_Tag(std::string _tag);
	std::vector<GameObject*> FindGameObject_Name(std::string _name);
};

