#include "ShapeTable3D.h"

//板
#define PLANE_VERTEX_NUM (4)
#define PLANE_INDEX_NUM (6)


//直方体
#define CUBE_VERTEX_NUM (24)
#define CUBE_INDEX_NUM (36)
#define CUBE_FASE_NUM (6)
#define CUBE_FASE_VERTEX_NUM (4)
#define CUBE_FASE_INDEX_NUM (6)


//球体
#define SQHERE_RADIUS (1.0f)
#define SQHERE_STACK_NUM (18)
#define SQHERE_SLICE_NUM (36)




/**
* @brief	３Dの四角形形状を作成する
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

	for (auto& vertex : plane->vertices)
	{
		vertex.color = { 1.f,1.f,1.f,1.f };
		vertex.normal = { 0.f,1.f,0.f };
	}

	plane->vertices[0].uv = { 0.f,0.f };
	plane->vertices[1].uv = { 1.f,0.f };
	plane->vertices[2].uv = { 0.f,1.f };
	plane->vertices[3].uv = { 1.f,1.f };

	plane->indices.resize(PLANE_INDEX_NUM);
	plane->indices = { 0,1,2,1,3,2 };

	plane->materials.push_back(hft::Material());
	plane->materials[0].shader.CreateVertexShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/02-LightMesh3D/VS_LightMesh3D.hlsl");
	plane->materials[0].shader.CreatePixelShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/01-Mesh3D/PS_Mesh3D.hlsl");

	return plane;
}

/**
* @brief	３Dの立方体を作成する
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
		vertices[8].position  = {  0.5f,  0.5f, -0.5f };	vertices[8].normal  = { 0.f,1.f,0.f };
		vertices[9].position  = { -0.5f,  0.5f, -0.5f };	vertices[9].normal  = { 0.f,1.f,0.f };
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
	
	cube->materials.push_back(hft::Material());
	cube->materials[0].shader.CreateVertexShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/02-LightMesh3D/VS_LightMesh3D.hlsl");
	cube->materials[0].shader.CreatePixelShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/01-Mesh3D/PS_Mesh3D.hlsl");

	return cube;
}

std::shared_ptr<hft::Mesh> CreateSqhereShape()
{
	auto sqhere = std::make_shared<hft::Mesh>();
	sqhere->name = "sqhere";

	//頂点作成＆格納
	for ( int i = 0; i <= SQHERE_STACK_NUM; i++ )
	{
		float phi = DirectX::XM_PI * i / SQHERE_STACK_NUM; //緯度 ( 0~π )半周 X軸の動き

		for ( int j = 0; j <= SQHERE_SLICE_NUM; j++ )
		{
			float theta = DirectX::XM_2PI * j / SQHERE_SLICE_NUM; //経度 ( 0~2π )一周 Y軸の動き

			float x = SQHERE_RADIUS * sinf(phi) * cosf(theta);
			float y = SQHERE_RADIUS * cosf(phi);
			float z = SQHERE_RADIUS * sinf(phi) * sinf(theta);

			hft::HFFLOAT3 position(x,y,z);
			hft::HFFLOAT3 normal = position; //球の中心からの方向 = 法線
			DirectX::XMVECTOR nrmVec = DirectX::XMLoadFloat3(&normal);
			nrmVec = DirectX::XMVector3Normalize(nrmVec);	//法線ベクトル作成
			DirectX::XMStoreFloat3(&normal, nrmVec);

			float u = theta / DirectX::XM_2PI;
			float v = phi / DirectX::XM_PI;

			hft::Vertex vertex;
			vertex.position = position;
			vertex.normal = normal;
			vertex.color = { 1.f,1.f,1.f,1.f };
			vertex.uv = { u,v };

			sqhere->vertices.push_back(vertex);
		}
	}	

	//インデックス作成＆格納
	for ( int i = 0; i < SQHERE_STACK_NUM; i++ )
	{
		for ( int j = 0; j < SQHERE_SLICE_NUM; j++ )
		{
			int first = i * (SQHERE_SLICE_NUM + 1) + j;
			int second = first + 1;
			int third = first + SQHERE_SLICE_NUM + 1;

			sqhere->indices.push_back(first);
			sqhere->indices.push_back(second);
			sqhere->indices.push_back(third);

			sqhere->indices.push_back(third);
			sqhere->indices.push_back(second);
			sqhere->indices.push_back(third + 1);
		}
	}

	sqhere->materials.push_back(hft::Material());
	sqhere->materials[0].shader.CreateVertexShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/02-LightMesh3D/VS_LightMesh3D.hlsl");
	sqhere->materials[0].shader.CreatePixelShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/01-Mesh3D/PS_Mesh3D.hlsl");

	return sqhere;
}


/**
* @brief	３Dの立方体を作成する
*/
std::shared_ptr<hft::Mesh> CreateLightShape()
{
	auto light = std::make_shared<hft::Mesh>();
	light->name = "light";

	auto& vertices = light->vertices;

	vertices.resize(CUBE_VERTEX_NUM);
	{	//POSITIVE_X
		vertices[0].position = { 0.5f,  0.5f, -0.5f };		vertices[0].normal = { -1.f,0.f,0.f };
		vertices[1].position = { 0.5f,  0.5f,  0.5f };		vertices[1].normal = { -1.f,0.f,0.f };
		vertices[2].position = { 0.5f, -0.5f, -0.5f };		vertices[2].normal = { -1.f,0.f,0.f };
		vertices[3].position = { 0.5f, -0.5f,  0.5f };		vertices[3].normal = { -1.f,0.f,0.f };
	}
	{	//NEGATIVE_X
		vertices[4].position = { -0.5f,  0.5f,  0.5f };		vertices[4].normal = { 1.f,0.f,0.f };
		vertices[5].position = { -0.5f,  0.5f, -0.5f };		vertices[5].normal = { 1.f,0.f,0.f };
		vertices[6].position = { -0.5f, -0.5f,  0.5f };		vertices[6].normal = { 1.f,0.f,0.f };
		vertices[7].position = { -0.5f, -0.5f, -0.5f };		vertices[7].normal = { 1.f,0.f,0.f };
	}
	{	//POSITIVE_Y
		vertices[8].position  = {  0.5f,  0.5f, -0.5f };	vertices[8].normal  = { 0.f,-1.f,0.f };
		vertices[9].position  = { -0.5f,  0.5f, -0.5f };	vertices[9].normal  = { 0.f,-1.f,0.f };
		vertices[10].position = {  0.5f,  0.5f,  0.5f };	vertices[10].normal = { 0.f,-1.f,0.f };
		vertices[11].position = { -0.5f,  0.5f,  0.5f };	vertices[11].normal = { 0.f,-1.f,0.f };
	}
	{	//NEGATIVE_Y
		vertices[12].position = {  0.5f, -0.5f,  0.5f };	vertices[12].normal = { 0.f,1.f,0.f };
		vertices[13].position = { -0.5f, -0.5f,  0.5f };	vertices[13].normal = { 0.f,1.f,0.f };
		vertices[14].position = {  0.5f, -0.5f, -0.5f };	vertices[14].normal = { 0.f,1.f,0.f };
		vertices[15].position = { -0.5f, -0.5f, -0.5f };	vertices[15].normal = { 0.f,1.f,0.f };
	}
	{	//POSITIVE_Z
		vertices[16].position = { 0.5f,  0.5f, 0.5f };		vertices[16].normal = { 0.f,0.f,-1.f };
		vertices[17].position = { -0.5f,  0.5f, 0.5f };		vertices[17].normal = { 0.f,0.f,-1.f };
		vertices[18].position = { 0.5f, -0.5f, 0.5f };		vertices[18].normal = { 0.f,0.f,-1.f };
		vertices[19].position = { -0.5f, -0.5f, 0.5f };		vertices[19].normal = { 0.f,0.f,-1.f };
	}
	{	//NEGATIVE_Z
		vertices[20].position = { -0.5f,  0.5f, -0.5f };	vertices[20].normal = { 0.f,0.f,1.f };
		vertices[21].position = {  0.5f,  0.5f, -0.5f };	vertices[21].normal = { 0.f,0.f,1.f };
		vertices[22].position = { -0.5f, -0.5f, -0.5f };	vertices[22].normal = { 0.f,0.f,1.f };
		vertices[23].position = {  0.5f, -0.5f, -0.5f };	vertices[23].normal = { 0.f,0.f,1.f };
	}

	//uv座標指定
	for (int i = 0; i < light->vertices.size(); i++)
	{
		light->vertices[i].color = { 1.f,1.f,1.f,1.f };

		switch (i % 4)
		{
		case 0: light->vertices[i].uv = { 0.f,0.f }; break;
		case 1: light->vertices[i].uv = { 1.f,0.f }; break;
		case 2: light->vertices[i].uv = { 0.f,1.f }; break;
		case 3: light->vertices[i].uv = { 1.f,1.f }; break;
		default: break;
		}
	}

	for (int i = 16, j = i; i + 4 > j; j++)
	{
		light->vertices[j].color = { 1,0,0,1 };
	}

	light->indices.resize(CUBE_INDEX_NUM);
	for (int i = 0; i < CUBE_FASE_NUM; i++)
	{
		int baseIndexNum = i * CUBE_FASE_INDEX_NUM;
		int baseVertexNum = i * CUBE_FASE_VERTEX_NUM;
		light->indices[baseIndexNum] = baseVertexNum;
		light->indices[baseIndexNum + 1] = baseVertexNum + 1;
		light->indices[baseIndexNum + 2] = baseVertexNum + 2;
		light->indices[baseIndexNum + 3] = baseVertexNum + 1;
		light->indices[baseIndexNum + 4] = baseVertexNum + 3;
		light->indices[baseIndexNum + 5] = baseVertexNum + 2;
	}

	light->materials.push_back(hft::Material());
	light->materials[0].shader.CreateVertexShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/01-Mesh3D/VS_Mesh3D.hlsl");
	light->materials[0].shader.CreatePixelShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/01-Mesh3D/PS_Mesh3D.hlsl");

	return light;
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

	{	//Sqhere
		auto sqhere = CreateSqhereShape();
		
		hft::CreateVertexIndexBuffer(sqhere);
		table.insert({sqhere->name,sqhere});
	}
	
	{	//Light
		auto light = CreateLightShape();
		hft::CreateVertexIndexBuffer(light);
		table.insert({ light->name,light });
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