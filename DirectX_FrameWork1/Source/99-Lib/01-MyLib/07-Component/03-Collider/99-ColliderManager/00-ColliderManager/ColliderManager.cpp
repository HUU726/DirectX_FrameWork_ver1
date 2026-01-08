#include "ColliderManager.h"

#include "../../../../01-System/System.h"
#include "../../01-Collider2D/00-Collider2D/Collider2D.h"
#include "../../02-Collider3D/00-Collider3D/Collider3D.h"
#include "../../../../06-GameObject/GameObject.h"

template<>
ColliderManager<Collider2D>::ColliderManager()
{
	type = COMP_MNG_TYPES::COMP_COLLIDER2D;
	System::GetInstance().AddCompMng(this);
}
template<>
void ColliderManager<Collider2D>::SelectCollider()
{
	li_enableCol.clear();
	preColliderPair.clear();
	curColliderPair.swap(preColliderPair);

	for ( auto collider : li_collider )
	{
		if ( collider->GetIsActive() )
			li_enableCol.push_back(collider);
	}
}


template<>
ColliderManager<Collider3D>::ColliderManager()
{
	type = COMP_MNG_TYPES::COMP_COLLIDER3D;
	System::GetInstance().AddCompMng(this);
}
template<>
void ColliderManager<Collider3D>::SelectCollider()
{
	li_enableCol.clear();
	preColliderPair.clear();
	curColliderPair.swap(preColliderPair);

	for ( auto collider : li_collider )
	{
		if ( collider->GetIsActive() )
			li_enableCol.push_back(collider);
	}

}




template<>
void ColliderManager<Collider2D>::CheckCollision()
{
	for ( int i = 0; i < li_enableCol.size(); i++ )
	{
		for ( int j = i + 1; j < li_enableCol.size(); j++ )
		{
			Collider2D* col1 = li_enableCol[i];
			Collider2D* col2 = li_enableCol[j];

			if ( col1 == col2 )
				return;

			if ( col1->CollideWith(col2) )
			{
				auto it = ColliderPair(col1,col2);
				curColliderPair.insert(it);
				//std::cout << col1 << "：" << col2 << " がヒットしました" << std::endl;
			}
		}
	}

	CheckPair();
}


template<>
void ColliderManager<Collider3D>::CheckCollision()
{
	for ( int i = 0; i < li_enableCol.size(); i++ )
	{
		for ( int j = i + 1; j < li_enableCol.size(); j++ )
		{
			Collider3D* col1 = li_enableCol[i];
			Collider3D* col2 = li_enableCol[j];

			if ( col1 == col2 )
				return;

			if ( col1->CollideWith(col2) )
			{
				auto it = ColliderPair(col1, col2);
				curColliderPair.insert(it);
				//std::cout << col1 << "：" << col2 << " がヒットしました" << std::endl;
			}
		}
	}

	CheckPair();
}


