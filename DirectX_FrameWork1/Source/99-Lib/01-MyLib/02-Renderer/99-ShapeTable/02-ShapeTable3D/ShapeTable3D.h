#pragma once

#include <d3d11.h>
#include <string>
#include <memory>
#include <unordered_map>

#include "../../99-Shape/Shape.h"
#include "../../../998-FH_Types/Vertex.h"





class ShapeTable3D
{
private:
	std::unordered_map<std::string, std::shared_ptr<Shape>> table;

	ShapeTable3D();

public:
	static ShapeTable3D& GetInstance()
	{
		static ShapeTable3D instance;
		return instance;
	}
	void AddShape(Shape& _shape);
	std::shared_ptr<Shape> GetShape(std::string _name) { return table[_name]; }
	void ClearTable();

};
