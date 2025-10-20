#include "Texture.h"
#include "stb_image.h"
#include "../01-System/System.h"

#include <iostream>



/***************************************************************************************************
* グローバル関数
***************************************************************************************************/
// テクスチャをロード
HRESULT LoadTexture(ID3D11Device* device, const char* filename, ID3D11ShaderResourceView** srv)
{
	bool sts = true;
	unsigned char* pixels;

	int m_width; // 幅
	int m_height; // 高さ
	int m_bpp; // BPP

	// 画像読み込み
	pixels = stbi_load(filename, &m_width, &m_height, &m_bpp, 4);
	if (pixels == nullptr) {
		MessageBoxA(NULL, filename, "load error", MB_OK);
		return S_FALSE;
	}

	// テクスチャ2Dリソース生成
	ID3D11Texture2D* pTexture;

	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = m_width;
	desc.Height = m_height;
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




/***************************************************************************************************
* Textureクラス
***************************************************************************************************/
void Texture::LoadTexture(std::string _filePath)
{
	static TextureTable& table = TextureTable::GetInstance();

	filePath = _filePath;
	wp_textureView = table.LoadTexture(_filePath);
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

std::weak_ptr<ID3D11ShaderResourceView> TextureTable::GetTexture(std::string _filePath)
{
	if (table.count(_filePath))
		return table[_filePath];

	
	std::cout << _filePath << "はテーブルに存在しないためロードします。" << std::endl;
	return this->LoadTexture(_filePath);
}

std::weak_ptr<ID3D11ShaderResourceView> TextureTable::LoadTexture(std::string _filePath)
{
	static RendererManager& system = RendererManager::GetInstance();

	auto sp_srv = std::shared_ptr<ID3D11ShaderResourceView>();
	ID3D11ShaderResourceView* p_srv = sp_srv.get();
	::LoadTexture(system.GetDevice(), _filePath.c_str(), &p_srv);
	table[_filePath] = sp_srv;
	return sp_srv;
}

void TextureTable::ReleaseTable()
{
	table.clear();
}
