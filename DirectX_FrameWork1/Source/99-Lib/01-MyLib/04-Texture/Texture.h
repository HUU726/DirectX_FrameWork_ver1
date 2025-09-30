#pragma once
#include <d3d11.h>
#include <string>
#include <memory>
#include <unordered_map>

HRESULT LoadTexture(ID3D11Device* device, const char* filename, ID3D11ShaderResourceView** srv);



struct Texture
{
	std::string filePath;	//ファイルパス
	std::weak_ptr<ID3D11ShaderResourceView> wp_textureView;

	void LoadTexture(std::string _filePath);
};

class TextureTable
{
private:
	std::unordered_map<std::string, std::shared_ptr<ID3D11ShaderResourceView>> table;

	TextureTable();
	~TextureTable();

public:
	static TextureTable& GetInstance()
	{
		static TextureTable instance;
		return instance;
	}

	std::weak_ptr<ID3D11ShaderResourceView> GetTexture(std::string _filePath);
	std::weak_ptr<ID3D11ShaderResourceView> LoadTexture(std::string _filePath);
	void ReleaseTable();

};