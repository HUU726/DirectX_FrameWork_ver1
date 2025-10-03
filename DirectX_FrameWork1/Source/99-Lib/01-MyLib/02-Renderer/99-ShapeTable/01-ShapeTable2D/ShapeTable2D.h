#pragma once

#include <d3d11.h>
#include <string>
#include <memory>
#include <unordered_map>

#include "../../99-Shape/Shape.h"
#include "../../../998-FH_Types/Vertex.h"





class ShapeTable2D
{
private:
	std::unordered_map<std::string, std::shared_ptr<Shape2D>> table;



	ShapeTable2D();

public:
	static ShapeTable2D& GetInstance()
	{
		static ShapeTable2D instance;
		return instance;
	}
	void SetShape(Shape2D& _shape);
	std::shared_ptr<Shape2D> GetShape(std::string _name) { return table[_name]; }

};

