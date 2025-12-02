#include "Collider3DManager.h"
#include "../../02-Collider3D/00-Collider3D/Collider3D.h"
#include "../../../../06-GameObject/GameObject.h"


#include <iostream>



Collider3DManager::Collider3DManager()
{

}


bool CubeCube(const Collider3D* _col1, const Collider3D* _col2)
{
    return false;
}

void Collider3DManager::AddCollider(Collider3D* _p_col)
{
    li_collider.push_back(_p_col);
}

void Collider3DManager::ClearCollider()
{
    li_collider.clear();
    li_enableCol.clear();
}

void Collider3DManager::RemoveCollider(Collider3D* _p_col)
{
    li_collider.erase(std::find(li_collider.begin(), li_collider.end(), _p_col));
}

void Collider3DManager::SelectCollider()
{
    li_enableCol.clear();
    for (auto collider : li_collider)
    {
        if (collider->GetGameObject()->GetIsActive())
            li_enableCol.push_back(collider);
    }
}

void Collider3DManager::CheckCollision()
{
    for (int i = 0; i < li_enableCol.size(); i++)
    {
        for (int j = i + 1; j < li_enableCol.size(); j++)
        {
            Collider3D* _p_col1 = li_enableCol[i];
            Collider3D* _p_col2 = li_enableCol[j];

            if (_p_col1 == _p_col2)
                return;

            if (_p_col1->CollideWith(_p_col2))
            {
                _p_col1->OnCollisionEnter(_p_col2);
                _p_col2->OnCollisionEnter(_p_col1);
                std::cout << _p_col1 << "F" << _p_col2 << " ‚ªƒqƒbƒg‚µ‚Ü‚µ‚½" << std::endl;
            }
        }

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