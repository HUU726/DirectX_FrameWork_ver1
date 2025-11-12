#include "Shader.h"

#include "../../02-Renderer/98-RendererManager/RendererManager.h"

void VertexShader::SetGPU()
{
	auto deviceContext = RendererManager::GetInstance().GetDeviceContext();
	deviceContext->VSSetShader(p_vertexShader, NULL, 0);
}

void VertexShader::CreateShader(std::string _filePath)
{
	
}




void PixelShader::SetGPU()
{
	auto deviceContext = RendererManager::GetInstance().GetDeviceContext();
	deviceContext->PSSetShader(p_pixelShader, NULL, 0);
}

void PixelShader::CreateShader(std::string _filePath)
{

}