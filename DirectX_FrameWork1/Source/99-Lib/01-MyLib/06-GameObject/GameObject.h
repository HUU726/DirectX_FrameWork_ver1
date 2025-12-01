#pragma once


/**
* @file		GameObjectクラスを作る		※基底クラス
* @date		2025/06/25
* @memo		色々なものの大本になるぞ―――
*/



#include <string>
#include <vector>
#include <memory>
#include "../07-Component/00-Component/Component.h"
#include "../07-Component/01-Transform/Transform.h"
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
	void AllDeleteComponent()
	{
		li_comp.clear();
	}

	int GetID() { return id; }
	const Transform& GetTransform() const { return *p_transform; }
	Transform* GetTransformPtr() { return p_transform; }
	std::string GetName() { return name; }
	std::string GetTag() { return tag; }
	bool GetIsActive() { return isActive; }
	bool GetIsRender() { return isRender; }

	void SetID(int _id) { id = _id; }
	void SetIsActive(bool _is) { isActive = _is; }
	void SetIsRender(bool _is) { isRender = _is; }

	void InitComponent();
	void UpdateComponent();

	virtual void OnCollisionEnter(Collider* _p_collider) {}
	virtual void OnCollisionStay(Collider* _p_collider) {}
	virtual void OnCollisionExit(Collider* _p_collider) {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() {};

};