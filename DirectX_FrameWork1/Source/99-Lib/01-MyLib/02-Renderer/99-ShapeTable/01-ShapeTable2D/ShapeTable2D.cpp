#include "ShapeTable2D.h"

#define TRIANGLE_VERTEX_NUM (3)
#define TRIANGLE_INDEX_NUM (3)

#define SPRITE_VERTEX_NUM (4)
#define SPRITE_INDEX_NUM (6)

#define CIRCLE_VERTEX_NUM (33)
#define CIRCLE_FASE_NUM (CIRCLE_VERTEX_NUM - 1)
#define CIRCLE_FASE_VERTEX_NUM (3)
#define CIRCLE_INDEX_NUM (CIRCLE_FASE_NUM * CIRCLE_FASE_VERTEX_NUM)



ShapeTable2D::ShapeTable2D()
{
}


void ShapeTable2D::AddShape(const hft::Polygon& _shape)
{
	if (table.count(_shape.name) == 0 )
	{
		auto shape = std::make_shared<hft::Polygon>(_shape);
		CreateVertexIndexBuffer(shape);
		table[shape->name] = shape;
	}
}
void ShapeTable2D::AddShape(const std::shared_ptr<hft::Polygon>& _sp_shape)
{
	std::string name = _sp_shape->name;
	if ( table.count(name) == 0 )
		table[name] = _sp_shape;

}

void ShapeTable2D::ClearTable()
{
	for ( auto& it : table )
	{
		it.second->p_vertexBuffer->Release();
		it.second->p_indexBuffer->Release();
	}
	std::unordered_map<std::string, std::shared_ptr<hft::Polygon>> swapTable;
	swapTable.swap(table);
}


void ShapeTable2D::Init()
{
	//三角形
	{
		auto triangle = std::make_shared<hft::Polygon>();
		triangle->name = "triangle";
		triangle->vertices.resize(TRIANGLE_VERTEX_NUM);

		triangle->vertices[0].position = { 0.f,0.5f,0.f,0.f };
		triangle->vertices[1].position = { 0.5f,-0.5f,0.f,0.f };
		triangle->vertices[2].position = { -0.5f,-0.5f,0.f,0.f };

		triangle->vertices[0].uv = { 0.5f,0.f };
		triangle->vertices[1].uv = { 0.f,1.f };
		triangle->vertices[2].uv = { 1.f,1.f };

		for (auto& vertex : triangle->vertices)
			vertex.color = { 1.f,1.f,1.f,1.f };

		triangle->indices = { 0,1,2 };

		CreateVertexIndexBuffer(triangle);
		table.insert({ triangle->name,triangle });
	}

	//四角形
	{
		auto sprite = std::make_shared<hft::Polygon>();
		sprite->name = "sprite";
		sprite->vertices.resize(SPRITE_VERTEX_NUM);
		sprite->vertices[0].position = { -0.5f,0.5f,0.f,1.f };
		sprite->vertices[0].color = { 1.f,1.f,1.f,1.f };
		sprite->vertices[0].uv = { 0.f,0.f };

		sprite->vertices[1].position = { 0.5f,0.5f,0.f,1.f };
		sprite->vertices[1].color = { 1.f,1.f,1.f,1.f };
		sprite->vertices[1].uv = { 1.f,0.f };

		sprite->vertices[2].position = { -0.5f,-0.5f,0.f,0.f };
		sprite->vertices[2].color = { 1.f,1.f,1.f,1.f };
		sprite->vertices[2].uv = { 0.f,1.f };

		sprite->vertices[3].position = { 0.5f,-0.5f,0.f,0.f };
		sprite->vertices[3].color = { 1.f,1.f,1.f,1.f };
		sprite->vertices[3].uv = { 1.f,1.f };

		sprite->indices = { 0,1,2,1,3,2 };

		CreateVertexIndexBuffer(sprite);
		table.insert({ sprite->name,sprite });
	}

	//円
	{
		auto circle = std::make_shared<hft::Polygon>();
		circle->name = "circle";
		circle->vertices.resize(CIRCLE_VERTEX_NUM);

		circle->vertices[0].position = { 0,0,0.f,0.f };
		circle->vertices[0].color = { 1.f,1.f,1.f,1.f };
		circle->vertices[0].uv = { 0.5f,0.5f };

		for (int i = 1; i < CIRCLE_VERTEX_NUM; i++)
		{
			float theta = DirectX::XM_2PI / (CIRCLE_VERTEX_NUM - 1) * i;
			float x = cos(theta);
			float y = sin(theta);
			circle->vertices[i].position = { x,y,0.f };
			circle->vertices[i].color = { 1.f,1.f,1.f,1.f };

			if (x >= 0)
				x = (x + 1.f) / 2.f;
			else
				x = (1.f + x) / 2.f;
			if (y >= 0)
				y = (y - 1.f) * -1.f / 2.f;
			else
				y = (-y + 1.f) / 2.f;

			circle->vertices[i].uv = { x,y };
		}

		//インデックス設定
		circle->indices.resize(CIRCLE_INDEX_NUM);
		for (int i = 0, biggerVertexNum = 2; i < CIRCLE_FASE_NUM; i++, biggerVertexNum++)
		{
			int baseIndexNum = i * CIRCLE_FASE_VERTEX_NUM;
			circle->indices[baseIndexNum] = 0;
			circle->indices[baseIndexNum + 1] = biggerVertexNum;
			circle->indices[baseIndexNum + 2] = biggerVertexNum - 1;
		}
		if (circle->indices[CIRCLE_INDEX_NUM - 2] == CIRCLE_VERTEX_NUM)
			circle->indices[CIRCLE_INDEX_NUM - 2] = 1;

		CreateVertexIndexBuffer(circle);
		table.insert({ circle->name,circle });
	}
}