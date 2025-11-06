#pragma once

#include <d3d11.h>
#include <string>
#include <memory>
#include <unordered_map>

#include "../../../998-FH_Types/Polygon.h"
#include "../../../998-FH_Types/Vertex.h"





class ShapeTable2D
{
private:
	std::unordered_map<std::string, std::shared_ptr<hft::Polygon>> table;

	ShapeTable2D();

public:
	static ShapeTable2D& GetInstance()
	{
		static ShapeTable2D instance;
		return instance;
	}
	void AddShape(hft::Polygon& _shape);
	std::shared_ptr<hft::Polygon> GetShape(std::string _name) { return table[_name]; }
	ID3D11Buffer* GetIndexBuffer(std::string _name) { return table[_name]->p_indexBuffer; }
	void ClearTable();

};

