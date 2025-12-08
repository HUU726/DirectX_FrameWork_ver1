#pragma once

#include <vector>
#include "../../../99-CompMng/IF_ComponentManager.h"

class Collider2D;

class Collider2DManager : public IF_ComponentManager
{
private:
	std::vector<Collider2D*> li_collider;	//Collider2Dのリスト
	std::vector<Collider2D*> li_enableCol;	//実際に当たり判定をとるコライダー

	Collider2DManager();

public:
	static Collider2DManager& GetInstance()
	{
		static Collider2DManager instance;
		return instance;
	}

	void AddCollider(Collider2D* _collider);
	void ClearCollider();
	void RemoveCollider(Collider2D* _p_col);

	void SelectCollider();	//当たり判定をとるコライダーを選別
	void CheckCollision();	//当たり判定をとる
	void Update();
	void UnInit();

	void Action() override;

};

