#pragma once
#include <d3d11.h>
#include <string>
#include <memory>
#include <unordered_map>

HRESULT LoadTexture(ID3D11Device* device, const char* filename, ID3D11ShaderResourceView** srv);



struct Texture
{
	std::string filePath;	//ファイルパス
	ID3D11ShaderResourceView* p_textureView;
	int width;
	int height;
	int bpp;
};

class TextureTable
{
private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> table;

	TextureTable();
	~TextureTable();

public:
	static TextureTable& GetInstance()
	{
		static TextureTable instance;
		return instance;
	}

	std::shared_ptr<Texture> GetTexture(std::string _filePath);
	std::shared_ptr<Texture> LoadTexture(std::string _filePath);
	void ReleaseTable();

};