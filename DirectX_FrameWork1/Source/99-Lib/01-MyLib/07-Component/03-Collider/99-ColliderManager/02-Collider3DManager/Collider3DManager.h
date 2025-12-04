#pragma once

#include <vector>
#include "../../../99-CompMng/IF_ComponentManager.h"

class Collider3D;


class Collider3DManager : public IF_ComponentManager
{
private:
	std::vector<Collider3D*> li_collider;	// Cllider3Dのリスト
	std::vector<Collider3D*> li_enableCol;	// 実際に当たり判定をとるコライダー

	Collider3DManager() {}

public:
	static Collider3DManager& GetInstance()
	{
		static Collider3DManager instance;
		return instance;
	}

	/**
	* @brief	コライダー追加
	* @param	Collider3D*		_p_col	3D用コライダーのポインタ
	*/
	void AddCollider(Collider3D* _p_col);
	/**
	* @brief	コライダー削除
	* @param	Collider3D*		_p_col	3D用コライダーのポインタ
	*/
	void RemoveCollider(Collider3D* _p_col);
	/**
	* @brief	コライダー全開放
	*/
	void ClearCollider();

	/**
	* @brief	実際に当たり判定をとるコライダーを選別
	*/
	void SelectCollider();	// 当たり判定をとるコライダーを選別
	/**
	* @brief	判定＆OnCollision系関数呼び出し
	*/
	void CheckCollision();	// 当たり判定をとる

	void Update();
	void UnInit();

	void Action() override;
};

