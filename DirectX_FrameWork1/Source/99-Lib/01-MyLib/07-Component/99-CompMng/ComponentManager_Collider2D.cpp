#include "ComponentManager.h"
#include "../03-Collider/01-Collider2D/00-Collider2D/Collider2D.h"

#include <iostream>


template<>
void ComponentManager<Collider2D>::Action()
{
	std::vector<Collider2D*> li_enableCol;
	for (auto& collider : compornents)
	{
		if (collider->GetIsActive())
			li_enableCol.push_back(collider);
	}


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
				col1->OnCollisionEnter2D(col2);
				col2->OnCollisionEnter2D(col1);
				std::cout << col1 << " F " << col2 << " A‚ªÕ“Ë‚µ‚Ü‚µ‚½" << std::endl;
			}
		}

	}
}