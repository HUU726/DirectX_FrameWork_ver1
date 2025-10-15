#include "Sprite2DRenderer.h"

#include "../../01-System/System.h"

#include "../../07-Component/01-Transform/Transform.h"
#include "../../998-FH_Types/Vertex.h"
#include "../../998-FH_Types/Sprite2D.h"
#include "../../998-FH_Types/TransformMatrix.h"

#include "../99-Shape/Shape.h"

#include "../../07-Component/04-Camera/01-Camera2D/Camera2D.h"
#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../06-GameObject/GameObject.h"

#define VERTEX_NUM_2D (4)

using hft::Vertex;
using hft::Sprite2D;
using hft::TransformMatrix;


Sprite2DRenderer::Sprite2DRenderer()
{
	Init();
}

HRESULT Sprite2DRenderer::InitShader()
{

	HRESULT hr;

	// インプットレイアウト作成
	D3D11_INPUT_ELEMENT_DESC layout[]
	{
		// 位置座標があるということを伝える
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// 色情報があるということを伝える
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// UV座標( uv )
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	const char* vsPath = "Source/99-Lib/01-MyLib/999-Shader/01-2D/01-Sprite2DShader/VS_Sprite2D.hlsl";
	hr = CreateVertexShader(&this->p_VertexShader, &this->p_InputLayout, layout, numElements, vsPath);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateVertexShader error", "error", MB_OK);
		return hr;
	}

	// ピクセルシェーダーオブジェクトを生成
	const char* psPath = "Source/99-Lib/01-MyLib/999-Shader/01-2D/01-Sprite2DShader/PS_Sprite2D.hlsl";
	hr = CreatePixelShader(&this->p_PixelShader, psPath);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreatePixelShader error", "error", MB_OK);
		return hr;
	}

	// 定数バッファ作成
	D3D11_BUFFER_DESC cdDesc;
	cdDesc.ByteWidth = sizeof(Sprite2DConstBuffer);
	cdDesc.Usage = D3D11_USAGE_DEFAULT;
	cdDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cdDesc.CPUAccessFlags = 0;
	cdDesc.MiscFlags = 0;
	cdDesc.StructureByteStride = 0;
	hr = this->p_Device->CreateBuffer(&cdDesc, NULL, &this->p_constantBuffer);
	if (FAILED(hr)) return hr;

	// 定数バッファ作成
	D3D11_BUFFER_DESC cdDesc;
	cdDesc.ByteWidth = sizeof(Sprite2DTextureCB);
	cdDesc.Usage = D3D11_USAGE_DEFAULT;
	cdDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cdDesc.CPUAccessFlags = 0;
	cdDesc.MiscFlags = 0;
	cdDesc.StructureByteStride = 0;
	hr = this->p_Device->CreateBuffer(&cdDesc, NULL, &this->p_PSConstantBuffer);
	if (FAILED(hr)) return hr;

	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	return S_OK;
}

HRESULT Sprite2DRenderer::InitBuffer()
{
	HRESULT hr;

	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.Usage = D3D11_USAGE_DYNAMIC;
	vbDesc.ByteWidth = sizeof(Vertex) * VERTEX_NUM_2D;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	hr = this->p_Device->CreateBuffer(&vbDesc, nullptr, &this->p_vertexBuffer); // 初期データなし
	if (FAILED(hr)) return hr;

	D3D11_BUFFER_DESC ibDesc = {};
	ibDesc.Usage = D3D11_USAGE_DYNAMIC;
	ibDesc.ByteWidth = sizeof(unsigned int) * VERTEX_NUM_2D;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	hr = this->p_Device->CreateBuffer(&ibDesc, nullptr, &this->p_indexBuffer);

	return S_OK;
}

HRESULT Sprite2DRenderer::InitState()
{
	HRESULT hr;

	// サンプラー作成
	// → テクスチャをポリゴンに貼るときに、拡大縮小される際のアルゴリズム
	D3D11_SAMPLER_DESC smpDesc{};
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = this->p_Device->CreateSamplerState(&smpDesc, &this->p_Sampler);
	if (FAILED(hr)) return hr;

	// ブレンドステート作成　→　透過処理や加算合成を可能にする色の合成方法
	D3D11_BLEND_DESC BlendState{};
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = FALSE;
	BlendState.IndependentBlendEnable = FALSE;
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = this->p_Device->CreateBlendState(&BlendState, &this->p_BlendState);
	if (FAILED(hr)) return hr;

	// 震度テストを無効にする)
	D3D11_DEPTH_STENCIL_DESC l_dsDesc;
	ZeroMemory(&l_dsDesc, sizeof(l_dsDesc));
	l_dsDesc.DepthEnable = FALSE;	//震度テストを無効にする
	l_dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	l_dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	hr = this->p_Device->CreateDepthStencilState(&l_dsDesc, &this->p_DSState);
	if (FAILED(hr)) return hr;

	return S_OK;
}


void Sprite2DRenderer::RenderPipeline()
{
	this->p_DeviceContext->IASetInputLayout(this->p_InputLayout);

	this->p_DeviceContext->IASetPrimitiveTopology(this->topology);
	this->p_DeviceContext->VSSetShader(this->p_VertexShader, NULL, 0);
	this->p_DeviceContext->PSSetShader(this->p_PixelShader, NULL, 0);

	// サンプラーをピクセルシェーダーに渡す
	this->p_DeviceContext->PSSetSamplers(0, 1, &this->p_Sampler);

	// 定数バッファを頂点シェーダーにセットする
	this->p_DeviceContext->VSSetConstantBuffers(0, 1, &this->p_constantBuffer);
	this->p_DeviceContext->PSSetConstantBuffers(0, 1, &this->p_PSConstantBuffer);

	// ブレンドステートをセットする
	this->p_DeviceContext->OMSetBlendState(this->p_BlendState, NULL, 0xffffffff);
	// デプスステンシルステートをセットする
	this->p_DeviceContext->OMSetDepthStencilState(this->p_DSState, 1);
}








void Sprite2DRenderer::SetCamera(Camera2D* _p_camera)
{
}

void Sprite2DRenderer::Draw(const Sprite2D* _sprite)
{

	if (p_camera == nullptr)
		return;

	RenderPipeline();


	TransformMatrix mtrxTf;
	mtrxTf.ConversionPosition(_sprite->p_transform->position);
	mtrxTf.ConversionRotation(_sprite->p_transform->rotation);
	mtrxTf.ConversionScale(_sprite->p_transform->scale);

	Sprite2DConstBuffer cb;	// 定数バッファを更新

	cb.matrixWorld = DirectX::XMMatrixTranspose(mtrxTf.GetMatrixWorld());	//ワールド変換行列
	cb.matrixProj = DirectX::XMMatrixTranspose(p_camera->GetMatrixProj());	//プロジェクション変換行列
	cb.matrixView = DirectX::XMMatrixTranspose(p_camera->GetMatrixView());	//ビュー変換行列

	//cb.matrixTex = DirectX::XMMatrixTranspose();
	cb.color = _sprite->vertices[0].color;
	cb.matrixTex = DirectX::XMMatrixIdentity();

	// 行列をシェーダーに渡す
	p_DeviceContext->UpdateSubresource(p_constantBuffer, 0, NULL, &cb, 0, 0);

	UINT strides = sizeof(Vertex);
	UINT offsets = 0;

	p_DeviceContext->IASetVertexBuffers(0, 1, &(this->p_vertexBuffer), &strides, &offsets);
	p_DeviceContext->IASetIndexBuffer(this->p_indexBuffer,DXGI_FORMAT_R32_UINT,0);
	p_DeviceContext->IASetPrimitiveTopology(topology);

	// テクスチャをピクセルシェーダーに渡す
	//p_DeviceContext->PSSetShaderResources(0, 1, &(_sprite->p_texture.p_textureView));

	p_DeviceContext->DrawIndexed(_sprite->indices.size(),0 , 0); // 描画命令
}

void Sprite2DRenderer::Draw(SpriteRenderer* _renderer)
{

	if (p_camera == nullptr)
		return;

	RenderPipeline();

	std::shared_ptr<Shape2D> shape = _renderer->GetShape();
	Transform* transform = _renderer->GetGameObject()->GetComponent<Transform>();

	TransformMatrix mtrxTf;
	mtrxTf.ConversionPosition(transform->position);
	mtrxTf.ConversionRotation(transform->rotation);
	mtrxTf.ConversionScale(transform->scale);

	{
		Sprite2DConstBuffer cb;	// 定数バッファを更新

		cb.matrixWorld = DirectX::XMMatrixTranspose(mtrxTf.GetMatrixWorld());	//ワールド変換行列
		cb.matrixProj = DirectX::XMMatrixTranspose(p_camera->GetMatrixProj());	//プロジェクション変換行列
		cb.matrixView = DirectX::XMMatrixTranspose(p_camera->GetMatrixView());	//ビュー変換行列

		//cb.matrixTex = DirectX::XMMatrixTranspose();
		cb.color = shape->vertices[0].color;
		cb.matrixTex = DirectX::XMMatrixIdentity();

		// 行列をシェーダーに渡す
		p_DeviceContext->UpdateSubresource(p_constantBuffer, 0, NULL, &cb, 0, 0);
	}

	{
		Sprite2DTextureCB cb;
		Texture* p_texture = _renderer->GetTexture();
		if (p_texture->wp_textureView.expired())
		{
			cb.isTexture = false;
		}
		else
		{
			cb.isTexture = true;
			//テクスチャをピクセルシェーダーに渡す
			ID3D11ShaderResourceView* textureView;
			if (p_texture->wp_textureView.lock().get() != nullptr)
				textureView = p_texture->wp_textureView.lock().get();
			p_DeviceContext->PSSetShaderResources(0, 1, &textureView);
		}

		p_DeviceContext->UpdateSubresource(p_PSConstantBuffer, 0, NULL, &cb, 0, 0);

	}

	UINT strides = sizeof(Vertex);
	UINT offsets = 0;

	p_DeviceContext->IASetVertexBuffers(0, 1, &(shape->p_vertexBuffer), &strides, &offsets);
	p_DeviceContext->IASetIndexBuffer(shape->p_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	p_DeviceContext->IASetPrimitiveTopology(topology);

	p_DeviceContext->DrawIndexed(shape->indices.size(), 0, 0); // 描画命令
}

void Sprite2DRenderer::Draw(const Shape2D* _shape, hft::HFFLOAT2 _pos, hft::HFFLOAT2 _scl, hft::HFFLOAT3 _rot)
{
}
