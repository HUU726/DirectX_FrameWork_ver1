#include "Shader.h"

#include "../../02-Renderer/98-RendererManager/RendererManager.h"
#include "../../02-Renderer/00-IF_Renderer/IF_Renderer.h"
#include "../99-ShaderTable/ShaderTable.h"
#include "../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"

#include <iostream>

namespace hft
{
	void VertexShader::SetGPU()
	{
		auto deviceContext = RendererManager::GetInstance().GetDeviceContext();
		deviceContext->IASetInputLayout(p_inputLayout);
		deviceContext->VSSetShader(p_vertexShader, NULL, 0);
	}

	void VertexShader::Release()
	{
		p_vertexShader->Release();
		p_inputLayout->Release();
	}





	void PixelShader::SetGPU()
	{
		auto deviceContext = RendererManager::GetInstance().GetDeviceContext();
		deviceContext->PSSetShader(p_pixelShader, NULL, 0);
	}

	void PixelShader::Release()
	{
		p_pixelShader->Release();
	}





	ID3D11InputLayout* Shader::GetInputLayout() const
	{
		if (!sp_vertexShader)
			nullptr;

		return sp_vertexShader->GetInputLayout();
	}

	bool Shader::GetHaveShader() const
	{
		if (!sp_vertexShader)
			return false;
		if (!sp_pixelShader)
			return false;

		return true;
	}

	ID3D11VertexShader* Shader::GetVertexShader() const
	{
		return sp_vertexShader->GetDirectXVertexShader();
		
	}

	ID3D11PixelShader* Shader::GetPixelShader() const
	{
		return sp_pixelShader->GetDirectXPixelShader();
	}

	void Shader::SetVertexShader(std::shared_ptr<VertexShader> _sp_shader)
	{
		sp_vertexShader = _sp_shader;
	}
	void Shader::SetPixelShader(std::shared_ptr<PixelShader> _sp_shader)
	{
		sp_pixelShader = _sp_shader;
	}

	void Shader::CreateVertexShader(std::string _filePath)
	{
		VertexShaderTable& table = VertexShaderTable::GetInstance();
		auto sp_shader = table.GetShader(_filePath);

		if (sp_shader)
		{
			std::cout << "すでに存在するVertexShaderのため、VertexShaderTableからロードしてください" << std::endl;
			sp_vertexShader = sp_shader;
			return;
		}

		sp_vertexShader = std::make_shared<VertexShader>();
		sp_vertexShader->SetFilePath(_filePath);

		// インプットレイアウト作成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT numElements = ARRAYSIZE(layout);

		ID3D11VertexShader* p_shader;
		ID3D11InputLayout* p_inputLayout;
		::CreateVertexShader(&p_shader, &p_inputLayout, layout, numElements, _filePath.c_str());
		
		sp_vertexShader->SetDirectXVertexShader(p_shader);
		sp_vertexShader->SetDirectXInputLayout(p_inputLayout);

		table.AddShader(sp_vertexShader);
	}

	void Shader::CreatePixelShader(std::string _filePath)
	{
		PixelShaderTable& table = PixelShaderTable::GetInstance();
		auto sp_shader = table.GetShader(_filePath);

		if (sp_shader)
		{
			std::cout << "すでに存在するVertexShaderのため、VertexShaderTableからロードしてください" << std::endl;
			sp_pixelShader = sp_shader;
			return;
		}

		sp_pixelShader = std::make_shared<PixelShader>();
		sp_pixelShader->SetFilePath(_filePath);
		ID3D11PixelShader* p_pixelShader;
		::CreatePixelShader(&p_pixelShader, _filePath.c_str());
		table.AddShader(sp_pixelShader);

		sp_pixelShader->SetDirectXPixelShader(p_pixelShader);
	}


	void Shader::SetGPU() const
	{
		sp_vertexShader->SetGPU();
		sp_pixelShader->SetGPU();
	}
}