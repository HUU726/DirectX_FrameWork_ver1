#pragma once
#include <d3d11.h>
#include <string>


HRESULT LoadTexture(ID3D11Device* device, const char* filename, ID3D11ShaderResourceView** srv);



struct Texture
{
	std::string filePath;	//ファイルパス

};