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
	GameObject* gameObject;

public:
	Component() : gameObject(nullptr) {};
	virtual ~Component() = default;

	void SetGameObject(GameObject* _p_gameObject) { this->gameObject = _p_gameObject; }
	GameObject* getGameObject() { return this->gameObject; }


	virtual void Init() = 0;
	virtual void Update() {}
	virtual void Draw() {}
};