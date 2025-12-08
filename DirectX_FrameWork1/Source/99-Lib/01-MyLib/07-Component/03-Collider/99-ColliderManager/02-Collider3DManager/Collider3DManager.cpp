#include "Collider3DManager.h"

#include "../../../../01-System/System.h"
#include "../../02-Collider3D/00-Collider3D/Collider3D.h"
#include "../../../../06-GameObject/GameObject.h"


#include <iostream>

Collider3DManager::Collider3DManager()
{
	type = COMP_MNG_TYPES::COMP_COLLIDER3D;
	System::GetInstance().AddCompMng(this);
}

void Collider3DManager::AddCollider(Collider3D* _p_collider)
{
    li_collider.push_back(_p_collider);
}

void Collider3DManager::ClearCollider()
{
    li_collider.clear();
    li_enableCol.clear();
}

void Collider3DManager::RemoveCollider(Collider3D* _p_collider)
{
	auto it = std::find(li_collider.begin(), li_collider.end(), _p_collider);

	if ( it != li_collider.end() )
	{
		li_collider.erase(it);
	}
}

void Collider3DManager::SelectCollider()
{
    li_enableCol.clear();
    for (auto collider : li_collider)
    {
		if ( collider->GetIsActive() )
		{
			li_enableCol.push_back(collider);
			collider->SwapHitColliders();
		}
    }
}

void Collider3DManager::CheckCollision()
{
    for (int i = 0; i < li_enableCol.size(); i++)
    {
        for (int j = i + 1; j < li_enableCol.size(); j++)
        {
            Collider3D* col1 = li_enableCol[i];
            Collider3D* col2 = li_enableCol[j];

            if (col1 == col2)
                return;

            if (col1->CollideWith(col2))
            {
				col1->AddCurHitCollider(col2);
				col2->AddCurHitCollider(col1);
                std::cout << col1 << "F" << col2 << " ‚ªƒqƒbƒg‚µ‚Ü‚µ‚½" << std::endl;
            }
        }
    }

	for ( auto collider : li_enableCol )
	{
		collider->CheckHitColliders();
	}
}

void Collider3DManager::Update()
{
    SelectCollider();
    CheckCollision();
}

void Collider3DManager::UnInit()
{
    ClearCollider();
}

void Collider3DManager::Action()
{
    Update();
}
