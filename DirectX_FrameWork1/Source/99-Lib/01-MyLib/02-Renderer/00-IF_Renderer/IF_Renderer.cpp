#include "IF_Renderer.h"
#include "../98-RendererManager/RendererManager.h"
<<<<<<< HEAD
#include "../../998-FH_Types/Vertex.h"
#include "../../998-FH_Types/TransformMatrix.h"
#include "../../07-Component/04-Camera/00-IF_Camera/IF_Camera.h"
=======
#include "../../07-Component/04-Camera/00-IF_Camera/IF_Camera.h"
#include "../../998-FH_Types/Vertex.h"
>>>>>>> 4e40d2ad3e76ecdcf30e95654a22433b59b29bb2

#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <locale.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>



VS_CB_MatrixVP VS_CB_MatrixVP::TransPose()
{
	VS_CB_MatrixVP vp;
	vp.view = DirectX::XMMatrixTranspose(view);
	vp.projection = DirectX::XMMatrixTranspose(projection);

	return vp;
}



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


<<<<<<< HEAD
void IF_Renderer::CreateCommonBuffer()
{
	HRESULT hr;

	{
		//PS定数バッファ作成
		D3D11_BUFFER_DESC PS_cdDesc;
		PS_cdDesc.ByteWidth = (sizeof(PS_CB_Texture) + 15) & ~15;
		PS_cdDesc.Usage = D3D11_USAGE_DEFAULT;
		PS_cdDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		PS_cdDesc.CPUAccessFlags = 0;
		PS_cdDesc.MiscFlags = 0;
		PS_cdDesc.StructureByteStride = 0;
		hr = this->p_Device->CreateBuffer(&PS_cdDesc, NULL, &this->p_PSConstantBuffer);
		if (FAILED(hr)) return;
	}

	{
		//VS定数バッファ作成
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
	{
		//VS定数バッファ作成
		D3D11_BUFFER_DESC cdDesc;
		cdDesc.ByteWidth = sizeof(VS_CB_VP);
		cdDesc.Usage = D3D11_USAGE_DEFAULT;
		cdDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cdDesc.CPUAccessFlags = 0;
		cdDesc.MiscFlags = 0;
		cdDesc.StructureByteStride = 0;
		hr = this->p_Device->CreateBuffer(&cdDesc, NULL, &this->p_constantVP);
		if (FAILED(hr)) return;
	}
}

void IF_Renderer::RenderPipeline()
{
	this->p_DeviceContext->IASetInputLayout(this->p_InputLayout);

	this->p_DeviceContext->IASetPrimitiveTopology(this->topology);

	this->p_DeviceContext->VSSetShader(this->p_VertexShader, NULL, 0);
	this->p_DeviceContext->PSSetShader(this->p_PixelShader, NULL, 0);

	// サンプラーをピクセルシェーダーに渡す
	this->p_DeviceContext->PSSetSamplers(0, 1, &this->p_SamplerState);

	// 定数バッファを頂点シェーダーにセットする
	this->p_DeviceContext->PSSetConstantBuffers(0, 1, &this->p_PSConstantBuffer);
	this->p_DeviceContext->VSSetConstantBuffers(0, 1, &p_constantWorld);
	this->p_DeviceContext->VSSetConstantBuffers(1, 1, &p_constantVP);

	// ブレンドステートをセットする
	this->p_DeviceContext->OMSetBlendState(this->p_BlendState, NULL, 0xffffffff);
	// ラスターライザステートをセットする
	this->p_DeviceContext->RSSetState(this->p_RRState);

	// デプスステンシルステートをセットする
	this->p_DeviceContext->OMSetDepthStencilState(this->p_DSState, 1);
=======
void IF_Renderer::RenderPipeline()
{
	//レイアウトをセットする
	p_DeviceContext->IASetInputLayout(this->p_InputLayout);

	//トポロジーをセットする
	p_DeviceContext->IASetPrimitiveTopology(this->topology);

	//シェーダーをセットする
	p_DeviceContext->VSSetShader(p_VertexShader, NULL, 0);
	p_DeviceContext->PSSetShader(p_PixelShader, NULL, 0);

	//サンプラーをピクセルシェーダーに渡す
	p_DeviceContext->PSSetSamplers(0, 1, &p_SamplerState);

	//ブレンドステートをセットする
	p_DeviceContext->OMSetBlendState(p_BlendState, NULL, 0xffffffff);
	//ラスターライザステートをセットする
	p_DeviceContext->RSSetState(p_RRState);
	//デプスステンシルステートをセットする
	p_DeviceContext->OMSetDepthStencilState(p_DSState, 1);

	//VP行列をセットする
	SetVPMatrix();
}

void IF_Renderer::InitCommonBuffer()
{
	HRESULT hr;
	//ワールド行列用定数バッファを作成
	{
		D3D11_BUFFER_DESC cbDesc;
		cbDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
		cbDesc.Usage = D3D11_USAGE_DEFAULT;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = 0;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;
		hr = p_Device->CreateBuffer(&cbDesc, NULL, &matrixWorld);
		if (FAILED(hr)) return;
	}

	//VP行列用定数バッファを作成
	{
		D3D11_BUFFER_DESC cbDesc;
		cbDesc.ByteWidth = sizeof(VS_CB_MatrixVP);
		cbDesc.Usage = D3D11_USAGE_DEFAULT;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = 0;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;
		hr = p_Device->CreateBuffer(&cbDesc, NULL, &matrixVP);
		if ( FAILED(hr) ) return;
	}

	//Texture使用するか否かの定数バッファ作成
	{
		D3D11_BUFFER_DESC cbDesc;
		cbDesc.ByteWidth = (sizeof(PS_CB_Texture) + 15) & ~15;
		cbDesc.Usage = D3D11_USAGE_DEFAULT;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = 0;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;
		hr = p_Device->CreateBuffer(&cbDesc, NULL, &enableTexture);
		if ( FAILED(hr) ) return;
	}
>>>>>>> 4e40d2ad3e76ecdcf30e95654a22433b59b29bb2
}

void IF_Renderer::Init()
{
	RendererManager* l_p_system = &RendererManager::GetInstance();
	this->p_Device = l_p_system->GetDevice();
	this->p_DeviceContext = l_p_system->GetDeviceContext();

	InitShader();
	InitBuffer();
<<<<<<< HEAD
	CreateCommonBuffer();
=======
>>>>>>> 4e40d2ad3e76ecdcf30e95654a22433b59b29bb2
	InitState();
}

IF_Renderer::IF_Renderer()
{
	RendererManager& l_p_system = RendererManager::GetInstance();
	p_Device = l_p_system.GetDevice();
	p_DeviceContext = l_p_system.GetDeviceContext();
	p_camera = nullptr;
	InitCommonBuffer();
}

<<<<<<< HEAD


void IF_Renderer::SetWorldMatrix(Transform& _transform)
{
	hft::TransformMatrix mtrxTf;
	mtrxTf.ConversionPosition(_transform.position);
	mtrxTf.ConversionRotation(_transform.rotation);
	mtrxTf.ConversionScale(_transform.scale);

	DirectX::XMMATRIX matWorld = DirectX::XMMatrixTranspose(mtrxTf.GetMatrixWorld());
	p_DeviceContext->UpdateSubresource(p_constantWorld, 0, NULL, &matWorld, 0, 0);
=======
void IF_Renderer::SetVertexBuffer(ID3D11Buffer* _p_vertexBuffer)
{
	UINT strides = sizeof(hft::Vertex);
	UINT offsets = 0;
	p_DeviceContext->IASetVertexBuffers(0,1,&_p_vertexBuffer,&strides,&offsets);
}

void IF_Renderer::SetIndexBuffer(ID3D11Buffer * _p_indexBuffer)
{
	p_DeviceContext->IASetIndexBuffer(_p_indexBuffer,DXGI_FORMAT_R32_UINT,0);
}

void IF_Renderer::SetWorldMatrix(const DirectX::XMMATRIX& _world)
{
	DirectX::XMMATRIX world = DirectX::XMMatrixTranspose(_world);

	p_DeviceContext->UpdateSubresource(matrixWorld, 0, NULL, &world, 0, 0);
	p_DeviceContext->VSSetConstantBuffers(0, 1, &matrixWorld);
>>>>>>> 4e40d2ad3e76ecdcf30e95654a22433b59b29bb2
}

void IF_Renderer::SetVPMatrix()
{
<<<<<<< HEAD
	{
		VS_CB_VP cb;
		cb.matProj = DirectX::XMMatrixTranspose(p_camera->GetMatrixProj());
		cb.matView = DirectX::XMMatrixTranspose(p_camera->GetMatrixView());

		p_DeviceContext->UpdateSubresource(p_constantVP, 0, NULL, &cb, 0, 0);
	}
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

void IF_Renderer::SetTexture(Texture* _p_texture)
{
	PS_CB_Texture cb;

	if (_p_texture == nullptr)
=======
	VS_CB_MatrixVP vp;
	vp.view = p_camera->GetMatrixView();
	vp.projection = p_camera->GetMatrixProj();

	vp.TransPose();

	p_DeviceContext->UpdateSubresource(matrixVP, 0, NULL, &vp, 0, 0);
	p_DeviceContext->VSSetConstantBuffers(1, 1, &matrixVP);
}

void IF_Renderer::SetTexture(const Texture& _texture)
{
	PS_CB_Texture cb;
	if ( _texture.wp_textureView.expired() )
>>>>>>> 4e40d2ad3e76ecdcf30e95654a22433b59b29bb2
	{
		cb.isTexture = false;
	}
	else
	{
<<<<<<< HEAD
		if (_p_texture->wp_textureView.expired())
		{
			cb.isTexture = false;
		}
		else
		{
			cb.isTexture = true;
			//テクスチャをピクセルシェーダーに渡す
			ID3D11ShaderResourceView* textureView = nullptr;
			if (_p_texture->wp_textureView.lock().get() != nullptr)
				textureView = _p_texture->wp_textureView.lock().get();
			p_DeviceContext->PSSetShaderResources(0, 1, &textureView);
		}
	}
	p_DeviceContext->UpdateSubresource(p_PSConstantBuffer, 0, NULL, &cb, 0, 0);
}


=======
		cb.isTexture = true;
		//テクスチャをピクセルシェーダーに渡す
		ID3D11ShaderResourceView* textureView = nullptr;
		if ( _texture.wp_textureView.lock().get() != nullptr )
			textureView = _texture.wp_textureView.lock().get();
		p_DeviceContext->PSSetShaderResources(0, 1, &textureView);
	}
	p_DeviceContext->UpdateSubresource(enableTexture, 0, NULL, &cb, 0, 0);
	p_DeviceContext->PSSetConstantBuffers(2, 1, &enableTexture);
}
>>>>>>> 4e40d2ad3e76ecdcf30e95654a22433b59b29bb2
