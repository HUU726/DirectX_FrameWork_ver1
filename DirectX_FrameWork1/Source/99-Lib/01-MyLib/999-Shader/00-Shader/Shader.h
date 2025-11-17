#pragma once

#include <d3d11.h>
#include <memory>
#include <string>

namespace hft
{

	class VertexShader
	{
	private:
		std::string filePath;
		ID3D11VertexShader* p_vertexShader;
		ID3D11InputLayout* p_inputLayout;
	
	public:
		VertexShader(){}
		void SetFilePath(std::string _filePath) { filePath = _filePath; }
		ID3D11VertexShader* GetDirectXVertexShader() { return p_vertexShader; }
		ID3D11InputLayout* GetInputLayout() { return p_inputLayout; }
		std::string GetFilePath();
		void SetDirectXVertexShader(ID3D11VertexShader* _p_shader) { p_vertexShader = _p_shader; }
		void SetDirectXInputLayout(ID3D11InputLayout* _p_inputLayout) { p_inputLayout = _p_inputLayout; }
		void SetGPU();
		void Release();

	};

	class PixelShader
	{
	private:
		std::string filePath;
		ID3D11PixelShader* p_pixelShader;

	public:
		PixelShader(){}
		std::string GetFilePath();
		ID3D11PixelShader* GetDirectXPixelShader() { return p_pixelShader; }
		void SetFilePath(std::string _filePath) { filePath = _filePath; }
		void SetDirectXPixelShader(ID3D11PixelShader* _p_shader) { p_pixelShader = _p_shader; }
		void SetGPU();
		void Release();

	};


	class Shader
	{
	private:
		std::shared_ptr<VertexShader> sp_vertexShader;
		std::shared_ptr<PixelShader> sp_pixelShader;

	public:
		void SetVertexShader(std::shared_ptr<VertexShader> _sp_shader);
		void SetPixelShader(std::shared_ptr<PixelShader> _sp_shader);
		void CreateVertexShader(std::string _filePath);
		void CreatePixelShader(std::string _filePath);

		void SetGPU() const;
	};

}