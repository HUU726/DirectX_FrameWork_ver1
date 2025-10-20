#include "ShapeTable2D.h"

#define TRIANGLE_VERTEX_NUM (3)
#define SPRITE_VERTEX_NUM (4)

#define CIRCLE_VERTEX_NUM (33)


ShapeTable2D::ShapeTable2D()
{
	{	//éOäpå`
		auto triangle = std::make_shared<Shape2D>();

		triangle->name = "triangle";
		triangle->vertices.resize(TRIANGLE_VERTEX_NUM);
		triangle->vertices[0].position = { 0.f,0.5f,0.f,0.f };
		triangle->vertices[0].color = { 1.f,1.f,1.f,1.f };
		triangle->vertices[0].uv = { 0.5f,0.f };

		triangle->vertices[1].position = { 0.5f,-0.5f,0.f,0.f };
		triangle->vertices[1].color = { 1.f,1.f,1.f,1.f };
		triangle->vertices[1].uv = { 0.f,1.f };

		triangle->vertices[2].position = { -0.5f,-0.5f,0.f,0.f };
		triangle->vertices[2].color = { 1.f,1.f,1.f,1.f };
		triangle->vertices[2].uv = { 1.f,1.f };

		triangle->indices = { 0,1,2 };

		CreateVertexIndexBuffer(triangle);
		table.insert({ triangle->name,triangle });
	}

	{	//éläpå`
		auto sprite = std::make_shared<Shape2D>();
		sprite->name = "sprite";
		sprite->vertices.resize(SPRITE_VERTEX_NUM);
		sprite->vertices[0].position = { -0.5f,0.5f,0.f,0.f };
		sprite->vertices[0].color = { 1.f,1.f,1.f,1.f };
		sprite->vertices[0].uv = { 0.f,0.f };

		sprite->vertices[1].position = { 0.5f,0.5f,0.f,0.f };
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

	return;

	{	//â~
		auto circle = std::make_shared<Shape2D>();
		circle->name = "circle";
		circle->vertices.resize(CIRCLE_VERTEX_NUM);

		circle->vertices[0].position = { 0,0,0.f,0.f };
		circle->vertices[0].color = { 1.f,1.f,1.f,1.f };

		for (int i = 1; i < CIRCLE_VERTEX_NUM - 1; i++)
		{
			float theta = DirectX::XM_2PI * i / (CIRCLE_VERTEX_NUM - 1);
			float x = cos(theta);
			float y = sin(theta);
			circle->vertices[i].position = { x,y,0.f,0.f };
			circle->vertices[i].color = { 1.f,1.f,1.f,1.f };
			circle->vertices[i].uv = { 0.5f,0.5f };

			if (x >= 0)
				x = (x - 1.f) * -1.f;
			else
				x = (-x + 1.f) / 2.f;
			if (y >= 0)
				y = (y - 1.f) * -1.f;
			else
				y = (-y + 1.f) / 2.f;

			circle->vertices[i].uv = { x,y };
		}
		
		CreateVertexIndexBuffer(circle);
		table.insert({ circle->name,circle });
	}

}

void ShapeTable2D::AddShape(Shape2D& _shape)
{
	if (table.count(_shape.name) != 0)
		return;

	table[_shape.name] = std::make_shared<Shape2D>(_shape);
}

void ShapeTable2D::ClearTable()
{
	table.clear();
}
