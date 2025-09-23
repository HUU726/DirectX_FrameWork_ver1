#include "Collider2DManager.h"
#include "../../01-Collider2D/00-Collider2D/Collider2D.h"
#include "../../../../06-GameObject/GameObject.h"

#include <iostream>

void Collider2DManager::AddCollider(Collider2D* _collider)
{
	li_collider.push_back(_collider);
}

void Collider2DManager::ClearCollider()
{
	li_collider.clear();
	li_enableCol.clear();
}

void Collider2DManager::RemoveCollider(Collider2D* _p_col)
{
	li_collider.erase(std::find(li_collider.begin(), li_collider.end(), _p_col));
}

void Collider2DManager::SelectCollider()
{
	li_enableCol.clear();
	for (auto collider : li_collider)
	{
		if (collider->GetGameObject()->GetIsActive())
			li_enableCol.push_back(collider);
	}
}

void Collider2DManager::CheckCollision()
{
	for (int i = 0; i < li_enableCol.size(); i++)
	{
		for (int j = i + 1; j < li_enableCol.size(); j++)
		{
			Collider2D* col1 = li_enableCol[i];
			Collider2D* col2 = li_enableCol[j];

			if (col1 == col2)
				continue;

			if (col1->CollideWith(col2))
			{
				col1->OnCollisionEnter(col2);
				col2->OnCollisionEnter(col1);
				//std::cout << col1 << " F " << col2 << " A‚ªÕ“Ë‚µ‚Ü‚µ‚½" << std::endl;
			}
		}

	}
}

void Collider2DManager::Update()
{
	SelectCollider();
	CheckCollision();
}

void Collider2DManager::UnInit()
{
	ClearCollider();
}
