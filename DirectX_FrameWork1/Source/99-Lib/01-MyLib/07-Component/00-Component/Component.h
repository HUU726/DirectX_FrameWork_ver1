#pragma once

#include <cstddef> // std::size_t のため
#include <type_traits> // std::is_base_of のため

/**
* @file		Componentクラスを作る	基底クラス
* @date		2025/06/25
* @memo		Colliderクラス,Soundクラスなどに継承
*/

class GameObject;


class Component
{
protected:
	GameObject* gameObject;	//自身を所有しているGameObjectのポインタ
	bool isActive;			//処理を実行するか否か

public:
	Component() : gameObject(nullptr), isActive(true) {};
	virtual ~Component() = default;

	/**
	* @brief	所有するGameObjectを設定
	* @param	GameObject*	_p_gameObject	ゲームオブジェクトポインタ
	* @note		GameObjectのAddComponent<T>();で呼び出し
	*/
	void SetGameObject(GameObject* _p_gameObject) { gameObject = _p_gameObject; }
	bool GetIsActive() const { return isActive; }
	GameObject* GetGameObject() const { return gameObject; }

	void SetIsActive(bool _is) { isActive = _is; }

	virtual void Init() = 0;
	virtual void Update() {}
	virtual void Draw() {}
	virtual void Action() {}	//独自の処理	※基本的にUpdateかDrawが入る
};