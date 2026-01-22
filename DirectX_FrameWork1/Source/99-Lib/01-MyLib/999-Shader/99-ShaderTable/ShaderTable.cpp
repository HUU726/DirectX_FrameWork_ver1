#include "ShaderTable.h"

#include "../../02-Renderer/00-IF_Renderer/IF_Renderer.h"
#include <iostream>

namespace hft
{
	VertexShaderTable::VertexShaderTable()
	{
	}

	std::shared_ptr<VertexShader> VertexShaderTable::GetShader(std::string _filePath) const
	{
		if (table.count(_filePath))
			return table.at(_filePath);

		return nullptr;
	}

	std::shared_ptr<VertexShader> VertexShaderTable::CreateShader(std::string _filePath)
	{
		if (GetShader(_filePath))
		{
			std::cout << "既に存在するVertexShaderのため、VertexShaderTableからロードします" << std::endl;
			return GetShader(_filePath);
		}

		return LoadVertexShader(_filePath);
	}

	void VertexShaderTable::AddShader(std::shared_ptr<VertexShader> _shader)
	{
		std::string filePath = _shader->GetFilePath();
		if (table.count(filePath))
			return;

		table[filePath] = _shader;
	}

	void VertexShaderTable::ClearTable()
	{
		for (auto& it : table)
		{
			it.second->Release();
		}

		std::unordered_map<std::string, std::shared_ptr<VertexShader>> swapTable;
		swapTable.swap(table);
	}

	void VertexShaderTable::Init()
	{

	}




	PixelShaderTable::PixelShaderTable()
	{

	}

	std::shared_ptr<PixelShader> PixelShaderTable::GetShader(std::string _filePath) const
	{
		if (table.count(_filePath))
		{
			return table.at(_filePath);
		}
		
		return nullptr;
	}

	std::shared_ptr<PixelShader> PixelShaderTable::CreateShader(std::string _filePath)
	{
		if ( GetShader(_filePath) )
		{
			std::cout << "既に存在するPixelShaderのため、PixelShaderTableからロードします" << std::endl;
			return GetShader(_filePath);
		}

		return LoadPixelShader(_filePath);
	}



	void PixelShaderTable::AddShader(std::shared_ptr<PixelShader> _shader)
	{
		std::string filePath = _shader->GetFilePath();
		if (table.count(filePath))
			return;

		table[filePath] = _shader;
	}

	void PixelShaderTable::ClearTable()
	{
		for (auto& it : table)
		{
			it.second->Release();
		}

		std::unordered_map<std::string, std::shared_ptr<PixelShader>> swapTable;
		swapTable.swap(table);
	}

	void PixelShaderTable::Init()
	{

	}


	std::shared_ptr<VertexShader> LoadVertexShader(std::string _filePath)
	{
		auto& table = VertexShaderTable::GetInstance();


		auto sp_vertexShader = std::make_shared<VertexShader>();
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
		HRESULT hr = ::CreateVertexShader(&p_shader, &p_inputLayout, layout, numElements, _filePath.c_str());
		if (FAILED(hr))
			return nullptr;

		sp_vertexShader->SetDirectXVertexShader(p_shader);
		sp_vertexShader->SetDirectXInputLayout(p_inputLayout);

		table.AddShader(sp_vertexShader);
		return sp_vertexShader;

	}
	std::shared_ptr<PixelShader> LoadPixelShader(std::string _filePath)
	{
		auto& table = PixelShaderTable::GetInstance();

		auto sp_pixelShader = std::make_shared<PixelShader>();
		sp_pixelShader->SetFilePath(_filePath);
		ID3D11PixelShader* p_pixelShader;
		HRESULT hr =::CreatePixelShader(&p_pixelShader, _filePath.c_str());
		if ( FAILED(hr) )
			return nullptr;
		
		table.AddShader(sp_pixelShader);

		sp_pixelShader->SetDirectXPixelShader(p_pixelShader);

		return sp_pixelShader;
	}
}