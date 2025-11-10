#include "IF_Renderer.h"
#include "../98-RendererManager/RendererManager.h"
#include "../../998-FH_Types/Vertex.h"
#include "../../998-FH_Types/TransformMatrix.h"

#include "../../07-Component/04-Camera/00-IF_Camera/IF_Camera.h"


#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <locale.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>




HRESULT IF_Renderer::CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ppShaderObject, int* pShaderObjectSize)
{
	//拡張子csoのファイル名を作成
	char csoFileName[256];
	const char* dot = strrchr(szFileName, '.');  // 最後の '.' を探す
	if (dot) {
		int basenameLen = dot - szFileName;
		strncpy_s(csoFileName, szFileName, basenameLen); // 拡張子がある場合は拡張子を除いたファイル名をコピー
		csoFileName[basenameLen] = '\0';   // 終端文字を追加
	}
	else {
		strcpy_s(csoFileName, szFileName);   // 拡張子がない場合はそのままコピー
	}
	strcat_s(csoFileName, ".cso");// ".cso" 拡張子を付加

	//csoファイルがあれば開く
	FILE* fp;
	int ret = fopen_s(&fp, csoFileName, "rb");
	if (ret == 0)
	{
		// ファイルサイズを取得
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		// バイナリデータを読み込み用にメモリ確保
		unsigned char* byteArray = new unsigned char[size];
		fread(byteArray, size, 1, fp);
		fclose(fp);

		// 呼び出し元にポインタとサイズを渡す
		*ppShaderObject = byteArray;
		*pShaderObjectSize = size;
	}
	//csoファイルがなければhlslファイルをコンパイルする
	else
	{
		HRESULT hr = S_OK;
		WCHAR	filename[512];
		size_t 	wLen = 0;
		int err = 0;

		// 文字コードを Shift-JIS → UTF-16 に変換
		setlocale(LC_ALL, "japanese");  // ロケールを設定（Windows特有）
		err = mbstowcs_s(&wLen, filename, 512, szFileName, _TRUNCATE);

		// シェーダーコンパイルオプションを設定
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		dwShaderFlags |= D3DCOMPILE_DEBUG; // デバッグビルドの場合はデバッグ情報も含める
#endif

		// コンパイル結果およびエラー情報格納用のBlob
		ID3DBlob* pErrorBlob = nullptr;
		ID3DBlob* pBlob = nullptr;

		// HLSLファイルをコンパイル
		hr = D3DCompileFromFile(
			filename,							// ファイル名
			nullptr,							// マクロ定義なし 
			D3D_COMPILE_STANDARD_FILE_INCLUDE,	// #include 対応 
			szEntryPoint,						// エントリーポイント名
			szShaderModel,						// シェーダーモデル
			dwShaderFlags,						// コンパイルフラグ
			0,									// エフェクトフラグ
			&pBlob,								// 成功時のコンパイル結果
			&pErrorBlob);						// コンパイルエラー出力

		// コンパイル失敗時のエラーメッセージを表示
		if (FAILED(hr))
		{
			if (pErrorBlob != nullptr) {
				MessageBoxA(NULL, (char*)pErrorBlob->GetBufferPointer(), "Error", MB_OK);
			}
			if (pErrorBlob) pErrorBlob->Release();
			if (pBlob)(pBlob)->Release();
			return E_FAIL;
		}

		// エラーブロブがあれば解放
		if (pErrorBlob) pErrorBlob->Release();

		// コンパイル成功時のバイナリデータを呼び出し元に渡す
		*ppShaderObject = (pBlob)->GetBufferPointer();
		*pShaderObjectSize = (pBlob)->GetBufferSize();
	}

	return S_OK;
}

HRESULT IF_Renderer::CreateVertexShader(ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout, D3D11_INPUT_ELEMENT_DESC* pLayout, unsigned int numElements, const char* szFileName)
{
	void* ShaderObject;
	int	ShaderObjectSize;

	// ファイルの拡張子に合わせてコンパイル
	HRESULT hr = CompileShader(szFileName, "main", "vs_5_0", &ShaderObject, &ShaderObjectSize);
	if (FAILED(hr)) return E_FAIL;

	// デバイスを使って頂点シェーダーを作成
	hr = this->p_Device->CreateVertexShader(ShaderObject, ShaderObjectSize, NULL, ppVertexShader);

	// デバイスを使って頂点レイアウトを作成
	this->p_Device->CreateInputLayout(pLayout, numElements, ShaderObject, ShaderObjectSize, ppVertexLayout);

	return S_OK;
}

HRESULT IF_Renderer::CreatePixelShader(ID3D11PixelShader** ppPixelShader, const char* szFileName)
{
	void* ShaderObject;
	int	ShaderObjectSize;

	// ファイルの拡張子に合わせてコンパイル
	HRESULT hr = CompileShader(szFileName, "main", "ps_5_0", &ShaderObject, &ShaderObjectSize);
	if (FAILED(hr)) return hr;

	// ピクセルシェーダーを生成
	hr = this->p_Device->CreatePixelShader(ShaderObject, ShaderObjectSize, nullptr, ppPixelShader);
	if (FAILED(hr)) return hr;

	return S_OK;
}


void IF_Renderer::CreateCommonBuffer()
{
	HRESULT hr;

	{	//PS定数バッファ作成
		D3D11_BUFFER_DESC PS_cbDesc;
		PS_cbDesc.ByteWidth = (sizeof(PS_CB_IsTexture) + 15) & ~15;
		PS_cbDesc.Usage = D3D11_USAGE_DEFAULT;
		PS_cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		PS_cbDesc.CPUAccessFlags = 0;
		PS_cbDesc.MiscFlags = 0;
		PS_cbDesc.StructureByteStride = 0;
		hr = this->p_Device->CreateBuffer(&PS_cbDesc, NULL, &this->p_PSConstantIsTexture);
		if (FAILED(hr)) return;
	}
	{	//PS定数バッファ作成
		D3D11_BUFFER_DESC PS_cbDesc;
		PS_cbDesc.ByteWidth = (sizeof(PS_CB_TexCoord) + 15) & ~15;
		PS_cbDesc.Usage = D3D11_USAGE_DEFAULT;
		PS_cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		PS_cbDesc.CPUAccessFlags = 0;
		PS_cbDesc.MiscFlags = 0;
		PS_cbDesc.StructureByteStride = 0;
		hr = this->p_Device->CreateBuffer(&PS_cbDesc, NULL, &this->p_PSConstantTexCoord);
		if (FAILED(hr)) return;
	}

	{	//VS定数バッファ作成
		D3D11_BUFFER_DESC cdDesc;
		cdDesc.ByteWidth = (sizeof(DirectX::XMMATRIX) + 15) & ~15;
		cdDesc.Usage = D3D11_USAGE_DEFAULT;
		cdDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cdDesc.CPUAccessFlags = 0;
		cdDesc.MiscFlags = 0;
		cdDesc.StructureByteStride = 0;
		hr = this->p_Device->CreateBuffer(&cdDesc, NULL, &this->p_constantWorld);
		if (FAILED(hr)) return;
	}
	{	//VS定数バッファ作成
		D3D11_BUFFER_DESC cdDesc;
		cdDesc.ByteWidth = (sizeof(VS_CB_VP) + 15) & ~15;
		cdDesc.Usage = D3D11_USAGE_DEFAULT;
		cdDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cdDesc.CPUAccessFlags = 0;
		cdDesc.MiscFlags = 0;
		cdDesc.StructureByteStride = 0;
		hr = this->p_Device->CreateBuffer(&cdDesc, NULL, &this->p_constantVP);
		if (FAILED(hr)) return;
	}
	{
		//VS定数バッファ作成
		D3D11_BUFFER_DESC cdDesc;
		cdDesc.ByteWidth = (sizeof(LightData) + 15) & ~15;
		cdDesc.Usage = D3D11_USAGE_DEFAULT;
		cdDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cdDesc.CPUAccessFlags = 0;
		cdDesc.MiscFlags = 0;
		cdDesc.StructureByteStride = 0;
		hr = this->p_Device->CreateBuffer(&cdDesc, NULL, &this->p_constantLight);
		if ( FAILED(hr) ) return;
	}

	{
		D3D11_BUFFER_DESC cbDesc;
		cbDesc.ByteWidth = (sizeof(hft::Material) + 15) & ~15;
		cbDesc.Usage = D3D11_USAGE_DEFAULT;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = 0;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;
		hr = this->p_Device->CreateBuffer(&cbDesc, NULL, &this->p_constantMaterial);
		if (FAILED(hr)) return;
	}
}

void IF_Renderer::RenderPipeline()
{
	this->p_DeviceContext->IASetInputLayout(this->p_InputLayout);

	this->p_DeviceContext->IASetPrimitiveTopology(this->topology);

	this->p_DeviceContext->VSSetShader(this->p_VertexShader, NULL, 0);
	this->p_DeviceContext->PSSetShader(this->p_PixelShader, NULL, 0);

	{
		// 定数バッファを頂点シェーダーにセットする
		this->p_DeviceContext->VSSetConstantBuffers(0, 1, &p_constantWorld);
		this->p_DeviceContext->VSSetConstantBuffers(1, 1, &p_constantVP);
		this->p_DeviceContext->VSSetConstantBuffers(3, 1, &p_constantLight);
	}
	{
		// サンプラーをピクセルシェーダーにセットする
		this->p_DeviceContext->PSSetSamplers(0, 1, &this->p_SamplerState);
		//定数バッファをピクセルシェーダーにセットする
		this->p_DeviceContext->PSSetConstantBuffers(2, 1, &p_PSConstantIsTexture);
	}

	// ブレンドステートをセットする
	this->p_DeviceContext->OMSetBlendState(this->p_BlendState, NULL, 0xffffffff);
	// ラスターライザステートをセットする
	this->p_DeviceContext->RSSetState(this->p_RRState);

	// デプスステンシルステートをセットする
	this->p_DeviceContext->OMSetDepthStencilState(this->p_DSState, 1);
}

void IF_Renderer::Init()
{
	RendererManager* l_p_system = &RendererManager::GetInstance();
	this->p_Device = l_p_system->GetDevice();
	this->p_DeviceContext = l_p_system->GetDeviceContext();

	InitShader();
	InitBuffer();
	CreateCommonBuffer();
	InitState();
}

IF_Renderer::IF_Renderer()
{
	RendererManager& l_p_system = RendererManager::GetInstance();
	p_Device = l_p_system.GetDevice();
	p_DeviceContext = l_p_system.GetDeviceContext();
	p_camera = nullptr;
}

IF_Renderer::~IF_Renderer()
{
	p_PSConstantIsTexture->Release();
	p_PSConstantTexCoord->Release();
	p_constantMaterial->Release();
	p_constantWorld->Release();
	p_constantVP->Release();
	p_constantLight->Release();
}



void IF_Renderer::SetWorldMatrix(Transform& _transform)
{
	hft::TransformMatrix mtrxTf;
	mtrxTf.ConversionPosition(_transform.position);
	mtrxTf.ConversionRotation(_transform.rotation);
	mtrxTf.ConversionScale(_transform.scale);

	DirectX::XMMATRIX matWorld = DirectX::XMMatrixTranspose(mtrxTf.GetMatrixWorld());
	p_DeviceContext->UpdateSubresource(p_constantWorld, 0, NULL, &matWorld, 0, 0);
}

void IF_Renderer::SetVPMatrix()
{
	{
		VS_CB_VP cb;
		cb.matProj = DirectX::XMMatrixTranspose(p_camera->GetMatrixProj());
		cb.matView = DirectX::XMMatrixTranspose(p_camera->GetMatrixView());

		p_DeviceContext->UpdateSubresource(p_constantVP, 0, NULL, &cb, 0, 0);
	}
}

void IF_Renderer::SetLight(const LightData& _data)
{
	p_DeviceContext->UpdateSubresource(p_constantLight, 0, NULL, &_data, 0, 0);
}

void IF_Renderer::SetVertexBuffer(ID3D11Buffer* _vertexBuffer)
{
	UINT strides = sizeof(hft::Vertex);
	UINT offsets = 0;
	p_DeviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &strides, &offsets);
}

void IF_Renderer::SetIndexBuffer(ID3D11Buffer* _indexBuffer)
{
	p_DeviceContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void IF_Renderer::SetTexture(std::shared_ptr<Texture> _sp_texture)
{
	PS_CB_IsTexture cb;

	if (!_sp_texture)
	{
		cb.isTexture = 0;
	}
	else
	{
		if (!_sp_texture->p_textureView)
		{
			cb.isTexture = 0;
		}
		else
		{
			cb.isTexture = 1;
			//テクスチャをピクセルシェーダーに渡す
			p_DeviceContext->PSSetShaderResources(0, 1, &_sp_texture->p_textureView);
		}
	}

	p_DeviceContext->UpdateSubresource(p_PSConstantIsTexture, 0, NULL, &cb, 0, 0);
}

void IF_Renderer::SetTex(hft::HFFLOAT2 _uv)
{
	DirectX::XMMATRIX l_matTex = DirectX::XMMatrixTranslation(_uv.x, _uv.y, 0.f);
	PS_CB_TexCoord cb;
	cb.matTex = DirectX::XMMatrixTranspose(l_matTex);

	p_DeviceContext->UpdateSubresource(p_PSConstantTexCoord, 0, NULL, &cb, 0, 0);
	p_DeviceContext->PSSetConstantBuffers(6, 1, &p_PSConstantTexCoord);
}

void IF_Renderer::SetMaterial(const hft::Material& _material)
{
	p_DeviceContext->UpdateSubresource(p_constantMaterial, 0, NULL, &_material, 0, 0);
	p_DeviceContext->VSGetConstantBuffers(4, 1, &p_constantMaterial);
	p_DeviceContext->PSGetConstantBuffers(4, 1, &p_constantMaterial);
}


