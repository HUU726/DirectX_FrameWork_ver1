#pragma once


#include <vector>

class Collider3D;

bool CubeCube(const Collider3D* _col1, const Collider3D* _col2);

class Collider3DManager
{
private:
	std::vector<Collider3D> li_collider;	// Cllider3Dのリスト
	std::vector<Collider3D> li_enableCol;	// 実際に当たり判定をとるコライダー

	Collider3DManager();

public:
	static Collider3DManager& GetInstance()
	{
		static Collider3DManager instance;
		return instance;
	}
	void SelectCollider();	// 当たり判定をとるコライダーを選別
	void CheckCollision();	// 当たり判定をとる

};

