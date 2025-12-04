#pragma once
#include "./00-Collider2D/Collider2D.h"


class BoxCollider2D : public Collider2D
{
private:
	std::vector<hft::HFFLOAT3> li_vertexWorldPos;	//ワールド変換した頂点座標コンテナ

public:
	bool CollideWith(Collider2D* _collider) override;
	bool CollideWithBox(Collider2D* _box) override;
	bool CollideWithCircle(Collider2D* _circle) override;
	bool CollideWithLine(Collider2D* _line) override;

	hft::HFFLOAT3 GetSize() const override;
	std::vector<hft::HFFLOAT3> GetVertexWorldPos() const { return li_vertexWorldPos; }

	void Init() override;
	void Update() override;
};

