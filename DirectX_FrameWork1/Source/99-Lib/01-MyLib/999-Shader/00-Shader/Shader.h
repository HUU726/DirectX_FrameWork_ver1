#pragma once

#include <d3d11.h>
#include <memory>
#include <string>

class VertexShader
{
private:
	std::string filePath;
	ID3D11VertexShader* p_vertexShader;
	
public:
	void SetGPU();

	void CreateShader(std::string _filePath);

};

class PixelShader
{
private:
	std::string filePath;
	ID3D11PixelShader* p_pixelShader;

public:
	void SetGPU();

	void CreateShader(std::string _filePath);

};
