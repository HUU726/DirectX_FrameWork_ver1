#pragma once

#include <d3d11.h>
#include <string>

struct Shape2D
{
	std::string name;	//形状名
	ID3D11Buffer* p_vertexBuffer;	//頂点バッファー
	ID3D11Buffer* p_indexBuffer;	//インデックスバッファー
};
