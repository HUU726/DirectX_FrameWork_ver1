#pragma once

#include <d3d11.h>
#include <string>

#include <vector>
#include <memory>
#include "../../998-FH_Types/Vertex.h"


struct Shape2D
{
	std::string name;					//形状名
	std::vector<hft::Vertex> vertices;	//頂点配列
	std::vector<unsigned int> indices;	//頂点順番
	ID3D11Buffer* p_vertexBuffer;		//頂点バッファー
	ID3D11Buffer* p_indexBuffer;		//インデックスバッファー
};


HRESULT CreateVertexIndexBuffer(std::shared_ptr<Shape2D> _sp_shape);