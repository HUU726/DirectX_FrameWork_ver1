#include "Texture.h"
#include "stb_image.h"
#include "../02-Renderer/98-RendererManager/RendererManager.h"

#include <iostream>



/***************************************************************************************************
* グローバル関数
***************************************************************************************************/
// テクスチャをロード
HRESULT LoadTexture(const char* _filePath, ID3D11ShaderResourceView** srv)
{
	
	auto device = RendererManager::GetInstance().GetDevice();

	bool sts = true;
	unsigned char* pixels;

	int l_width; // 幅
	int l_height; // 高さ
	int l_bpp; // BPP

	// 画像読み込み
	pixels = stbi_load(_filePath, &l_width, &l_height, &l_bpp, 4);
	if (pixels == nullptr) {
		MessageBoxA(NULL, _filePath, "load error", MB_OK);
		return S_FALSE;
	}

	// テクスチャ2Dリソース生成
	ID3D11Texture2D* pTexture;

	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = l_width;
	desc.Height = l_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // RGBA
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = pixels;
	subResource.SysMemPitch = desc.Width * 4; // RGBA = 4 bytes per pixel
	subResource.SysMemSlicePitch = 0;

	HRESULT hr = device->CreateTexture2D(&desc, &subResource, &pTexture);
	if (FAILED(hr)) {
		stbi_image_free(pixels);
		return hr;
	}

	// SRV生成
	hr = device->CreateShaderResourceView(pTexture, nullptr, srv);
	if (FAILED(hr)) {
		stbi_image_free(pixels);
		return hr;
	}

	// ピクセルイメージ解放
	stbi_image_free(pixels);

	return S_OK;
}

HRESULT LoadTextureFromMemory(const unsigned char* _data, int _len, ID3D11ShaderResourceView** srv)
{
	auto device = RendererManager::GetInstance().GetDevice();

	bool sts = true;
	unsigned char* pixels;

	int l_width; // 幅
	int l_height; // 高さ
	int l_bpp; // BPP

	// 画像読み込み
	pixels = stbi_load_from_memory(_data,
		_len,
		&l_width,
		&l_height,
		&l_bpp,
		STBI_rgb_alpha);

	// テクスチャ2Dリソース生成
	ID3D11Texture2D* pTexture;

	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = l_width;
	desc.Height = l_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // RGBA
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = pixels;
	subResource.SysMemPitch = desc.Width * 4; // RGBA = 4 bytes per pixel
	subResource.SysMemSlicePitch = 0;

	HRESULT hr = device->CreateTexture2D(&desc, &subResource, &pTexture);
	if ( FAILED(hr) )
	{
		stbi_image_free(pixels);
		return hr;
	}

	// SRV生成
	hr = device->CreateShaderResourceView(pTexture, nullptr, srv);
	if ( FAILED(hr) )
	{
		stbi_image_free(pixels);
		return hr;
	}

	// ピクセルイメージ解放
	stbi_image_free(pixels);

	return S_OK;
}




/***************************************************************************************************
* TextureTableクラス
***************************************************************************************************/
TextureTable::TextureTable()
{

}

TextureTable::~TextureTable()
{
	table.clear();
}

std::shared_ptr<Texture> TextureTable::GetTexture(std::string _filePath)
{
	if (table.count(_filePath))
		return table[_filePath];

	return nullptr;
}

std::shared_ptr<Texture> TextureTable::LoadTexture(std::string _filePath)
{
	if (table.count(_filePath) == 0 )
	{
		RendererManager& rendererMng = RendererManager::GetInstance();

		auto sp_texture = std::make_shared<Texture>();
		ID3D11ShaderResourceView* p_srv = sp_texture->p_textureView;
		::LoadTexture(_filePath.c_str(), &sp_texture->p_textureView);

		std::cout << _filePath << "はテーブルに存在しないためロードします。" << std::endl;
		table[_filePath] = sp_texture;
		return sp_texture;
	}
	else
	{
		std::cout << _filePath << "は既にロードされているためポインタを渡します。" << std::endl;
		return GetTexture(_filePath);
	}
}

void TextureTable::ReleaseTable()
{
	table.clear();
}
