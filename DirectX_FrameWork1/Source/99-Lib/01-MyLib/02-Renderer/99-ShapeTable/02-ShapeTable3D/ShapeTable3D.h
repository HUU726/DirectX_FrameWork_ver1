#pragma once

#include <d3d11.h>
#include <string>
#include <memory>
#include <unordered_map>

#include "../../../998-FH_Types/Mesh.h"
#include "../../../998-FH_Types/Vertex.h"





class ShapeTable3D
{
private:
	std::unordered_map<std::string, std::shared_ptr<hft::Mesh>> table;

	ShapeTable3D();

public:
	static ShapeTable3D& GetInstance()
	{
		static ShapeTable3D instance;
		return instance;
	}
	void AddShape(hft::Mesh& _shape);
	void AddShape(std::shared_ptr<hft::Mesh> _sp_shape);
	std::shared_ptr<hft::Mesh> GetShape(std::string _name) const { return table.at(_name); }
	void ClearTable();

};
