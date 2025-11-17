#include "ShaderTable.h"


namespace hft
{
	VertexShaderTable::VertexShaderTable()
	{
	}

	std::shared_ptr<VertexShader> VertexShaderTable::GetShader(std::string _filePath)
	{
		if (table.count(_filePath))
			return table[_filePath];

		return nullptr;
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
		table.clear();
	}






	PixelShaderTable::PixelShaderTable()
	{

	}

	std::shared_ptr<PixelShader> PixelShaderTable::GetShader(std::string _filePath)
	{
		if (table.count(_filePath))
			return table[_filePath];

		return nullptr;
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
		table.clear();
	}



	void LoadVertexShader(std::string _filePath)
	{
		auto& table = VertexShaderTable::GetInstance();
		auto sp_shader = table.GetShader(_filePath);

		if (sp_shader)
		{

		}
	}
	void LoadPixelShader(std::string _filePath)
	{
		auto& table = PixelShaderTable::GetInstance();
		auto sp_shader = table.GetShader(_filePath);

		if (sp_shader)
		{

		}
	}
}