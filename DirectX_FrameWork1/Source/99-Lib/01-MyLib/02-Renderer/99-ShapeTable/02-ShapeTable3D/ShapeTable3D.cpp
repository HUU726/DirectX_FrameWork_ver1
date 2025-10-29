#include "ShapeTable3D.h"


#define PLANE_VERTEX_NUM (4)
#define PLANE_INDEX_NUM (6)

#define CUBE_VERTEX_NUM (24)
#define CUBE_INDEX_NUM (36)
#define CUBE_FASE_NUM (6)
#define CUBE_FASE_VERTEX_NUM (4)
#define CUBE_FASE_INDEX_NUM (6)


/**
* @brief	ÇRDÇÃéläpå`å`èÛÇçÏê¨Ç∑ÇÈ
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
	{
		vertex.color = { 1.f,1.f,1.f,1.f };
		vertex.normal = { 1.f,1.f,1.f };
	}

	plane->indices = { 0,1,2,1,3,2 };

	return plane;
}

/**
* @brief	ÇRDÇÃóßï˚ëÃÇçÏê¨Ç∑ÇÈ
*/
std::shared_ptr<hft::Mesh> CreateCubeShape()
{
	auto cube = std::make_shared<hft::Mesh>();
	cube->name = "cube";

	auto& vertices = cube->vertices;

	vertices.resize(CUBE_VERTEX_NUM);
	{	//POSITIVE_X
		vertices[0].position = { 0.5f,  0.5f, -0.5f };		vertices[0].normal = { 1.f,0.f,0.f };
		vertices[1].position = { 0.5f,  0.5f,  0.5f };		vertices[1].normal = { 1.f,0.f,0.f };
		vertices[2].position = { 0.5f, -0.5f, -0.5f };		vertices[2].normal = { 1.f,0.f,0.f };
		vertices[3].position = { 0.5f, -0.5f,  0.5f };		vertices[3].normal = { 1.f,0.f,0.f };
	}
	{	//NEGATIVE_X
		vertices[4].position = { -0.5f,  0.5f,  0.5f };		vertices[4].normal = { -1.f,0.f,0.f };
		vertices[5].position = { -0.5f,  0.5f, -0.5f };		vertices[5].normal = { -1.f,0.f,0.f };
		vertices[6].position = { -0.5f, -0.5f,  0.5f };		vertices[6].normal = { -1.f,0.f,0.f };
		vertices[7].position = { -0.5f, -0.5f, -0.5f };		vertices[7].normal = { -1.f,0.f,0.f };
	}
	{	//POSITIVE_Y
		vertices[8].position  = {  0.5f,  0.5f, -0.5f };	vertices[8].normal = { 0.f,1.f,0.f };
		vertices[9].position  = { -0.5f,  0.5f, -0.5f };	vertices[9].normal = { 0.f,1.f,0.f };
		vertices[10].position = {  0.5f,  0.5f,  0.5f };	vertices[10].normal = { 0.f,1.f,0.f };
		vertices[11].position = { -0.5f,  0.5f,  0.5f };	vertices[11].normal = { 0.f,1.f,0.f };
	}
	{	//NEGATIVE_Y
		vertices[12].position = {  0.5f, -0.5f,  0.5f };	vertices[12].normal = { 0.f,-1.f,0.f };
		vertices[13].position = { -0.5f, -0.5f,  0.5f };	vertices[13].normal = { 0.f,-1.f,0.f };
		vertices[14].position = {  0.5f, -0.5f, -0.5f };	vertices[14].normal = { 0.f,-1.f,0.f };
		vertices[15].position = { -0.5f, -0.5f, -0.5f };	vertices[15].normal = { 0.f,-1.f,0.f };
	}
	{	//POSITIVE_Z
		vertices[16].position = {  0.5f,  0.5f, 0.5f };		vertices[16].normal = { 0.f,0.f,1.f };
		vertices[17].position = { -0.5f,  0.5f, 0.5f };		vertices[17].normal = { 0.f,0.f,1.f };
		vertices[18].position = {  0.5f, -0.5f, 0.5f };		vertices[18].normal = { 0.f,0.f,1.f };
		vertices[19].position = { -0.5f, -0.5f, 0.5f };		vertices[19].normal = { 0.f,0.f,1.f };
	}
	{	//NEGATIVE_Z
		vertices[20].position = { -0.5f,  0.5f, -0.5f };	vertices[20].normal = { 0.f,0.f,-1.f };
		vertices[21].position = {  0.5f,  0.5f, -0.5f };	vertices[21].normal = { 0.f,0.f,-1.f };
		vertices[22].position = { -0.5f, -0.5f, -0.5f };	vertices[22].normal = { 0.f,0.f,-1.f };
		vertices[23].position = {  0.5f, -0.5f, -0.5f };	vertices[23].normal = { 0.f,0.f,-1.f };
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