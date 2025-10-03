#include "ShapeTable2D.h"

void ShapeTable2D::SetShape(Shape2D& _shape)
{
	if (table.count(_shape.name) != 0)
		return;

	table[_shape.name] = std::make_shared<Shape2D>(_shape);
}
