#pragma once


/**
* @file		GameObjectクラスを作る		※基底クラス
* @date		2025/06/25
* @memo		色々なものの大本になるぞ―――
*/



#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "../07-Component/01-Transform/Transform.h"
#include "../101-Time/Time.h"
#include "Time.h"

class Collider;

class GameObject
{
protected:
	int id;					//オブジェクトID
	std::string name;		//オブジェクト名
	std::string tag;		//タグ
	std::vector<std::unique_ptr<Component>> li_comp;		//コンポーネントリスト
	Transform* p_transform;
	bool isActive;
	bool isRender;

public:
	GameObject();
	~GameObject();

	/**
	* @brief	コンポーネントを追加
	* @param	コンポーネントごとのコンストラクタ引数
	* @return	コンポーネントのポインタ
	* @memo		AddComponent<T>();	T：コンポネントの型
	*/
	template <class T, class... Args>
	T* AddComponent(Args&&... args)
	{
		auto comp = std::make_unique<T>(std::forward<Args>(args)...);
		comp->SetGameObject(this);
		T* compPtr = comp.get();
		compPtr->Init();
		this->li_comp.push_back(std::move(comp));
		return compPtr;
	}
	/**
	* @brief	コンポーネントを取得
	* @return	コンポーネントポインタ
	* @memo		GetComponent<T>();	T：コンポネントの型
	*/
	template<class T>
	T* GetComponent()
	{
		for (auto& comp : this->li_comp)
		{
			if (auto compType = dynamic_cast<T*>(comp.get()))
				return compType;
		}
		//return AddComponent<T>();
		return nullptr;
	}
	/**
	* @brief	コンポネントを削除
	* @memo		DeleteComponent<T>();	T：コンポネントの型
	*/
	template<class T>
	void DeleteComponent()
	{
		for (auto& comp : this->li_comp)
		{
			if (auto& up_comp = dynamic_cast<std::unique_ptr<T>>(comp))
			{
				auto it = std::find(li_comp.begin(), li_comp.end(), comp);
				li_comp.erase(it);
				up_comp.release();
			}
		}
	}
	/**
	* @brief	全てのコンポネントを削除
	*/
	void AllDeleteComponent()
	{
		li_comp.clear();
	}

	int GetID() const { return id; }
	/**
	* @brief	トランスフォームのデータ取得
	*/
	const Transform& GetTransform() const { return *p_transform; }
	/**
	* @brief	トランスフォームのポインタ取得
	*/
	Transform* GetTransformPtr() const { return p_transform; }
	std::string GetName() const { return name; }
	std::string GetTag() const { return tag; }
	bool GetIsActive() const { return isActive; }
	bool GetIsRender() const { return isRender; }

	void SetID(int _id) { id = _id; }
	void SetIsActive(bool _is) { isActive = _is; }
	void SetIsRender(bool _is) { isRender = _is; }

	void InitComponent();
	void UpdateComponent();

	virtual void OnCollisionEnter(Collider* _p_collider) {}
	virtual void OnCollisionStay(Collider* _p_collider) {}
	virtual void OnCollisionExit(Collider* _p_collider) {}

	//========================UnityでいうScriptに当たる========================
	/**
	* @brief	初期化
	*/
	virtual void Init() = 0;

	/**
	* @brief	毎フレーム更新処理
	*/
	virtual void Update() = 0;
	//==========================================================================

	virtual void Draw() {};

};