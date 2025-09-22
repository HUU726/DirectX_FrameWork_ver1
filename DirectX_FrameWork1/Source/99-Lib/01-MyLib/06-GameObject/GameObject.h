#pragma once


/**
* @file		GameObjectクラスを作る		※基底クラス
* @date		2025/06/25
* @memo		色々なものの大本になるぞ―――
*/



#include <string>
#include <vector>
#include <memory>
#include "../99-Lib/01-MyLib/97-Component/00-Component/Component.h"
#include "../99-Lib/01-MyLib/105-TypeSup/TypeSup.h"
#include "Time.h"


class GameObject
{
protected:
	int id;					//オブジェクトID
	std::string name;		//オブジェクト名
	std::string tag;		//タグ
	Transform* transform;	// トランスフォーム
	std::vector<std::unique_ptr<Component>> li_comp;		//コンポーネントリスト
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

	Transform& GetTransform() { return *transform; }
	Transform* GetTransformPtr() { return transform; }
	std::string GetName() { return name; }
	std::string GetTag() { return tag; }
	bool GetIsActive() { return isActive; }
	bool GetIsRender() { return isRender; }

	void SetIsActive(bool _is) { isActive = _is; }
	void SetIsRender(bool _is) { isRender = _is; }

	void InitComponent();
	void UpdateComponent();
	virtual void Draw();

	virtual void Init() = 0;
	virtual void Update() = 0;
};