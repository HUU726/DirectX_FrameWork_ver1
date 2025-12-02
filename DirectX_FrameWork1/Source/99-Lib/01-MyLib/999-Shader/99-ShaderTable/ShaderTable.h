#pragma once

#include "../00-Shader/Shader.h"
#include <unordered_map>


namespace hft
{

	/**
	* @brief	VertexShaderTable
	* @date		2025/11/13
	*/
	class VertexShaderTable
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<VertexShader>> table;

		VertexShaderTable();


	public:
		static VertexShaderTable& GetInstance()
		{
			static VertexShaderTable instance;
			return instance;
		}

		std::shared_ptr<VertexShader> GetShader(std::string _filePath) const;
		std::shared_ptr<VertexShader> CreateShader(std::string _filePath);

		void AddShader(std::shared_ptr<VertexShader> _shader);
		void ClearTable();

	};

	/**
	* @brief	PixelShader
	* @date		2025/11/13
	*/
	class PixelShaderTable
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<PixelShader>> table;

		PixelShaderTable();

	public:
		static PixelShaderTable& GetInstance()
		{
			static PixelShaderTable instance;
			return instance;
		}

		std::shared_ptr<PixelShader> GetShader(std::string _filePath) const;
		std::shared_ptr<PixelShader> CreateShader(std::string _filePath);

		void AddShader(std::shared_ptr<PixelShader> _shader);
		void ClearTable();

	};


	std::shared_ptr<VertexShader> LoadVertexShader(std::string _filePath);
	std::shared_ptr<PixelShader> LoadPixelShader(std::string _filePath);

}
