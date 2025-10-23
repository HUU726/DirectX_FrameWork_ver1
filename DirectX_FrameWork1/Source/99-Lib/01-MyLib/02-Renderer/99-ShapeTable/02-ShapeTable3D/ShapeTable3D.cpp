#include "ShapeTable3D.h"


#define PLANE_VERTEX_NUM (4)
#define PLANE_INDEX_NUM (6)

#define CUBE_VERTEX_NUM (24)
#define CUBE_INDEX_NUM (36)
#define CUBE_FASE_NUM (6)
#define CUBE_FASE_VERTEX_NUM (4)
#define CUBE_FASE_INDEX_NUM (6)


/**
* @brief	‚RD‚ÌlŠpŒ`Œ`ó‚ğì¬‚·‚é
* @date		2025/10/22
*/
std::shared_ptr<hft::Mesh> CreatePlaneShape()
{
	auto plane = std::make_shared<hft::Mesh>();
	plane->name = "plane";

	plane->vertices.resize(PLANE_VERTEX_NUM);
	plane->vertices[0].position = { -0.5f, 0.f,  0.5f};
	plane->vertices[1].position = {  0.5f, 0.f,  0.5f};
	plane->vertices[2].position = { -0.5f, 0.f, -0.5f};
	plane->vertices[3].position = {  0.5f, 0.f, -0.5f};

	plane->indices.resize(PLANE_INDEX_NUM);
	plane->vertices[0].uv = { 0.f,0.f };
	plane->vertices[1].uv = { 1.f,0.f };
	plane->vertices[2].uv = { 0.f,1.f };
	plane->vertices[3].uv = { 1.f,1.f };

	for (auto& vertex : plane->vertices)
		vertex.color = {1.f,1.f,1.f,1.f};

	plane->indices = { 0,1,2,1,3,2 };

	return plane;
}

/**
* @brief	‚RD‚Ì—§•û‘Ì‚ğì¬‚·‚é
*/
std::shared_ptr<hft::Mesh> CreateCubeShape()
{
	auto cube = std::make_shared<hft::Mesh>();
	cube->name = "cube";

	cube->vertices.resize(CUBE_VERTEX_NUM);
	{	//POSITIVE_X
		cube->vertices[0].position = { 0.5f,  0.5f, -0.5f };
		cube->vertices[1].position = { 0.5f,  0.5f,  0.5f };
		cube->vertices[2].position = { 0.5f, -0.5f, -0.5f };
		cube->vertices[3].position = { 0.5f, -0.5f,  0.5f };
	}
	{	//NEGATIVE_X
		cube->vertices[4].position = { -0.5f,  0.5f,  0.5f };
		cube->vertices[5].position = { -0.5f,  0.5f, -0.5f };
		cube->vertices[6].position = { -0.5f, -0.5f,  0.5f };
		cube->vertices[7].position = { -0.5f, -0.5f, -0.5f };
	}
	{	//POSITIVE_Y
		cube->vertices[8].position  = {  0.5f,  0.5f, -0.5f };
		cube->vertices[9].position  = { -0.5f,  0.5f, -0.5f };
		cube->vertices[10].position = {  0.5f,  0.5f,  0.5f };
		cube->vertices[11].position = { -0.5f,  0.5f,  0.5f };
	}
	{	//NEGATIVE_Y
		cube->vertices[12].position = { -0.5f, -0.5f,  0.5f };
		cube->vertices[13].position = {  0.5f, -0.5f,  0.5f };
		cube->vertices[14].position = { -0.5f, -0.5f, -0.5f };
		cube->vertices[15].position = {  0.5f, -0.5f, -0.5f };
	}
	{	//POSITIVE_Z
		cube->vertices[16].position = {  0.5f,  0.5f, 0.5f };
		cube->vertices[17].position = { -0.5f,  0.5f, 0.5f };
		cube->vertices[18].position = {  0.5f, -0.5f, 0.5f };
		cube->vertices[19].position = { -0.5f, -0.5f, 0.5f };
	}
	{	//NEGATIVE_Z
		cube->vertices[20].position = { -0.5f,  0.5f, -0.5f };
		cube->vertices[21].position = {  0.5f,  0.5f, -0.5f };
		cube->vertices[22].position = { -0.5f, -0.5f, -0.5f };
		cube->vertices[23].position = {  0.5f, -0.5f, -0.5f };
	}

	for (int i = 0; i < cube->vertices.size(); i++)
	{
		cube->vertices[i].color = { 1.f,1.f,1.f,1.f };
		
		switch (i%4)
		{
		case 0: cube->vertices[i].uv = { 0.f,0.f }; break;
		case 1: cube->vertices[i].uv = { 1.f,0.f }; break;
		case 2: cube->vertices[i].uv = { 0.f,1.f }; break;
		case 3: cube->vertices[i].uv = { 1.f,1.f }; break;
		default: break;
		}
	}

	cube->indices.resize(CUBE_INDEX_NUM);
	for (int i = 0; i < CUBE_FASE_NUM; i++)
	{
		int baseIndexNum = i * CUBE_FASE_INDEX_NUM;
		int baseVertexNum = i * CUBE_FASE_VERTEX_NUM;
		cube->indices[baseIndexNum] = baseVertexNum;
		cube->indices[baseIndexNum + 1] = baseVertexNum + 1;
		cube->indices[baseIndexNum + 2] = baseVertexNum + 2;
		cube->indices[baseIndexNum + 3] = baseVertexNum + 1;
		cube->indices[baseIndexNum + 4] = baseVertexNum + 3;
		cube->indices[baseIndexNum + 5] = baseVertexNum + 2;
	}
	
	return cube;
}

ShapeTable3D::ShapeTable3D()
{
	{	//Plane
		auto plane = CreatePlaneShape();

		hft::CreateVertexIndexBuffer(plane);
		table.insert({plane->name,plane});
	}

	{	//Cube
		auto cube = CreateCubeShape();

		hft::CreateVertexIndexBuffer(cube);
		table.insert({cube->name,cube});
	}
}

void ShapeTable3D::AddShape(hft::Mesh& _shape)
{
	table[_shape.name] = std::make_shared<hft::Mesh>(_shape);
}

void ShapeTable3D::ClearTable()
{
	table.clear();
}