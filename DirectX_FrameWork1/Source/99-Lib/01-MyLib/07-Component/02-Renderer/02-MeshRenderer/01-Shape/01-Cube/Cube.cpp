#include "Cube.h"




void Cube::CreateVerticesAndIndex()
{
	// 頂点情報初期化
	{
		vertices.resize(24);
		// 表面
		vertices[0] = { {-0.5,  0.5, -0.5}, {0.f,0.f,0.f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
		vertices[1] = { { 0.5,  0.5, -0.5}, {0.f,0.f,0.f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
		vertices[2] = { {-0.5, -0.5, -0.5}, {0.f,0.f,0.f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
		vertices[3] = { { 0.5, -0.5, -0.5}, {0.f,0.f,0.f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
		// 裏面
		vertices[4] = { {-0.5,  0.5,  0.5}, {0.f,0.f,0.f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
		vertices[5] = { { 0.5,  0.5,  0.5}, {0.f,0.f,0.f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
		vertices[6] = { {-0.5, -0.5,  0.5}, {0.f,0.f,0.f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
		vertices[7] = { { 0.5, -0.5,  0.5}, {0.f,0.f,0.f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
		// 右面
		vertices[8] = { {0.5,  0.5, -0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
		vertices[9] = { {0.5,  0.5,  0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
		vertices[10] = { {0.5, -0.5, -0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
		vertices[11] = { {0.5, -0.5,  0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
		// 左面
		vertices[12] = { {-0.5,  0.5,  0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
		vertices[13] = { {-0.5,  0.5, -0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
		vertices[14] = { {-0.5, -0.5,  0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
		vertices[15] = { {-0.5, -0.5, -0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
		// 上面
		vertices[16] = { {-0.5, 0.5,  0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
		vertices[17] = { { 0.5, 0.5,  0.5},  {0.f,0.f,0.f} ,{1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
		vertices[18] = { {-0.5, 0.5, -0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
		vertices[19] = { { 0.5, 0.5, -0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
		// 下面
		vertices[20] = { {-0.5, -0.5,  0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} };
		vertices[21] = { { 0.5, -0.5,  0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} };
		vertices[22] = { {-0.5, -0.5, -0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} };
		vertices[23] = { { 0.5, -0.5, -0.5}, {0.f,0.f,0.f} , {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} };
	}

	// 頂点結び方情報初期化
	{
		indices.resize(36);
		// 表面
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 2;
		indices[4] = 1;
		indices[5] = 3;
		// 裏面
		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 6;
		indices[9] = 6;
		indices[10] = 5;
		indices[11] = 7;
		// 右面
		indices[12] = 8;
		indices[13] = 9;
		indices[14] = 10;
		indices[15] = 10;
		indices[16] = 9;
		indices[17] = 11;
		// 左面
		indices[18] = 12;
		indices[19] = 13;
		indices[20] = 14;
		indices[21] = 14;
		indices[22] = 13;
		indices[23] = 15;
		// 上面
		indices[24] = 16;
		indices[25] = 17;
		indices[26] = 18;
		indices[27] = 18;
		indices[28] = 17;
		indices[29] = 19;
		// 下面
		indices[30] = 20;
		indices[31] = 21;
		indices[32] = 22;
		indices[33] = 22;
		indices[34] = 21;
		indices[35] = 23;
	}
}

Cube::Cube()
{
	CreateVerticesAndIndex();
}

Cube::Cube(const Transform& _transform)
{
	//p_transform = new	Transform(_transform);

	CreateVerticesAndIndex();
}

Cube::Cube(Transform* _p_transform)
{
	//p_transform = _p_transform;

	CreateVerticesAndIndex();
}

Cube::~Cube()
{

}
