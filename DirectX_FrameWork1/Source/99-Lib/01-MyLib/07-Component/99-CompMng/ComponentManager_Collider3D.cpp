#include "ComponentManager.h"

#include <iostream>
#include "../03-Collider/02-Collider3D/00-Collider3D/Collider3D.h"

template<>
void ComponentManager<Collider3D>::Action()
{
	std::vector<Collider3D*> li_enableCol;
	for (auto& collider : components)
	{
		if (collider->GetIsActive())
		{
			li_enableCol.push_back(collider);
			collider->SwapHitColliders();
		}
	}


	for (int i = 0; i < li_enableCol.size(); i++)
	{
		for (int j = i + 1; j < li_enableCol.size(); j++)
		{
			Collider3D* col1 = li_enableCol[i];
			Collider3D* col2 = li_enableCol[j];

			if (col1 == col2)
				continue;

			if (col1->CollideWith(col2))
			{
				col1->AddCurHitCollider(col2);
				col2->AddCurHitCollider(col1);
				//std::cout << col1 << " F " << col2 << " A‚ªÕ“Ë‚µ‚Ü‚µ‚½" << std::endl;
			}
		}
	}

	for ( auto collider : li_enableCol )
	{
		collider->CheckHitColliders();
	}
}