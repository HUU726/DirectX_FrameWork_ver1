#include "Sprite2DRenderer.h"

#include "../98-RendererManager/RendererManager.h"

#include "../../07-Component/01-Transform/Transform.h"
#include "../../998-FH_Types/Vertex.h"
#include "../../998-FH_Types/Sprite2D.h"
#include "../../998-FH_Types/TransformMatrix.h"

#include "../../998-FH_Types/Polygon.h"

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
	std::vector<D3D11_INPUT_ELEMENT_DESC> l_layout
	{
		// 位置座標があるということを伝える
		(D3D11_INPUT_ELEMENT_DESC{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }),
		// 法線情報があるということを伝える
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// 色情報があるということを伝える
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// UV座標( uv )
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	l_layout.swap(this->layouts);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	VS_Path = "Source/99-Lib/01-MyLib/999-Shader/01-2D/01-Sprite2DShader/VS_Sprite2D.hlsl";
	hr = CreateVertexShader(&this->p_VertexShader, &this->p_InputLayout, layouts.data(), layouts.size(), VS_Path);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateVertexShader error", "error", MB_OK);
		return hr;
	}

	// ピクセルシェーダーオブジェクトを生成
	PS_Path = "Source/99-Lib/01-MyLib/999-Shader/01-2D/01-Sprite2DShader/PS_Sprite2D.hlsl";
	hr = CreatePixelShader(&this->p_PixelShader, PS_Path);
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
	D3D11_BUFFER_DESC PS_cdDesc;
	PS_cdDesc.ByteWidth = (sizeof(Sprite2DTextureCB) + 15) & ~15;
	PS_cdDesc.Usage = D3D11_USAGE_DEFAULT;
	PS_cdDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	PS_cdDesc.CPUAccessFlags = 0;
	PS_cdDesc.MiscFlags = 0;
	PS_cdDesc.StructureByteStride = 0;
	hr = this->p_Device->CreateBuffer(&PS_cdDesc, NULL, &this->p_PSConstantBuffer);
	if (FAILED(hr)) return hr;

	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	return S_OK;
}

HRESULT Sprite2DRenderer::InitBuffer()
{
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
	hr = this->p_Device->CreateSamplerState(&smpDesc, &this->p_SamplerState);
	if (FAILED(hr)) return hr;

	// ブレンドステート作成　→　透過処理や加算合成を可能にする色の合成方法
	D3D11_BLEND_DESC blendDesc{};
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.AlphaToCoverageEnable = FALSE;						 // アルファ・トゥ・カバレッジを無効化（透明度をカバレッジとして利用しない）
	blendDesc.IndependentBlendEnable = FALSE;						 // 各レンダーターゲットに対して個別のブレンド設定を有効化
	blendDesc.RenderTarget[0].BlendEnable = TRUE;					 // ブレンドを無効に設定（不透明な描画）
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;		// ソース（描画するピクセル）のアルファ値を使用
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;	// デスティネーション（既存のピクセル）の逆アルファ値を使用
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;			// ソースとデスティネーションを加算する操作
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;		// ソースのアルファ値をそのまま使用
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;	// デスティネーションのアルファ値を無視
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;	// アルファ値に対して加算操作を行う
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;	// レンダーターゲットのカラーチャンネル書き込みマスク
	hr = this->p_Device->CreateBlendState(&blendDesc, &this->p_BlendState);
	if (FAILED(hr)) return hr;

	// ラスターライザステート作成
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID; //ソリッド
	//rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME; //ワイヤーフレーム
	rasterizerDesc.CullMode = D3D11_CULL_BACK; //ポリゴン裏をカリング
	//rasterizerDesc.CullMode = D3D11_CULL_FRONT; //ポリゴン表をカリング
	//rasterizerDesc.CullMode = D3D11_CULL_NONE; //カリングしない(裏も表も表示される)
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;
	hr = p_Device->CreateRasterizerState(&rasterizerDesc, &p_RRState);
	if (FAILED(hr)) return hr;
	p_DeviceContext->RSSetState(p_RRState);

	// 震度テストを無効にする
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.DepthEnable = TRUE;	//震度テストを無効にする
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	hr = this->p_Device->CreateDepthStencilState(&dsDesc, &this->p_DSState);
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
	this->p_DeviceContext->PSSetSamplers(0, 1, &this->p_SamplerState);

	// 定数バッファを頂点シェーダーにセットする
	this->p_DeviceContext->VSSetConstantBuffers(0, 1, &this->p_constantBuffer);
	this->p_DeviceContext->PSSetConstantBuffers(0, 1, &this->p_PSConstantBuffer);

	// ブレンドステートをセットする
	this->p_DeviceContext->OMSetBlendState(this->p_BlendState, NULL, 0xffffffff);
	// ラスターライザステートをセットする
	this->p_DeviceContext->RSSetState(this->p_RRState);

	// デプスステンシルステートをセットする
	this->p_DeviceContext->OMSetDepthStencilState(this->p_DSState, 1);
}


void Sprite2DRenderer::SetCamera(Camera2D* _p_camera)
{
	p_camera = _p_camera;
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

	p_DeviceContext->DrawIndexed(_sprite->indices.size(),0 , 0); // 描画命令
}

void Sprite2DRenderer::Draw(SpriteRenderer* _renderer)
{

	if (p_camera == nullptr)
		return;

	RenderPipeline();

	std::shared_ptr<hft::Polygon> shape = _renderer->GetShape();
	if (!shape)
		return;

	Transform* transform = _renderer->GetGameObject()->GetTransformPtr();

	TransformMatrix mtrxTf;
	mtrxTf.ConversionPosition(transform->position);
	mtrxTf.ConversionRotation(transform->rotation);
	mtrxTf.ConversionScale(transform->scale);

	{	//VS用定数バッファ更新
		Sprite2DConstBuffer cb;

		cb.color = shape->vertices[0].color;

		DirectX::XMMATRIX matrixTex = DirectX::XMMatrixTranslation(0.f, 0.f, 0.0f);
		cb.matrixTex = DirectX::XMMatrixTranspose(matrixTex);

		cb.matrixWorld = DirectX::XMMatrixTranspose(mtrxTf.GetMatrixWorld());	//ワールド変換行列
		cb.matrixProj = DirectX::XMMatrixTranspose(p_camera->GetMatrixProj());	//プロジェクション変換行列
		cb.matrixView = DirectX::XMMatrixTranspose(p_camera->GetMatrixView());	//ビュー変換行列

		// 行列をシェーダーに渡す
		p_DeviceContext->UpdateSubresource(p_constantBuffer, 0, NULL, &cb, 0, 0);
	}

	{	//PS用定数バッファ更新
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
			ID3D11ShaderResourceView* textureView = nullptr;
			if (p_texture->wp_textureView.lock().get() != nullptr)
				textureView = p_texture->wp_textureView.lock().get();
			p_DeviceContext->PSSetShaderResources(0, 1, &textureView);
		}

		p_DeviceContext->UpdateSubresource(p_PSConstantBuffer, 0, NULL, &cb, 0, 0);

	}

	UINT strides = sizeof(hft::Vertex);
	UINT offsets = 0;

	p_DeviceContext->IASetVertexBuffers(0, 1, &(shape->p_vertexBuffer), &strides, &offsets);
	p_DeviceContext->IASetIndexBuffer(shape->p_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	p_DeviceContext->DrawIndexed(static_cast<UINT>(shape->indices.size()), 0, 0); // 描画命令
}

void Sprite2DRenderer::Draw(const hft::Polygon& _shape, hft::HFFLOAT4 _pos, hft::HFFLOAT3 _scl, hft::HFFLOAT3 _rot)
{
	if (p_camera == nullptr)
		return;

	RenderPipeline();

	TransformMatrix mtrxTf;
	mtrxTf.ConversionPosition(_pos);
	mtrxTf.ConversionRotation(_rot);
	mtrxTf.ConversionScale(_scl);

	{
		Sprite2DConstBuffer cb;	// 定数バッファを更新

		cb.matrixWorld = DirectX::XMMatrixTranspose(mtrxTf.GetMatrixWorld());	//ワールド変換行列
		cb.matrixProj = DirectX::XMMatrixTranspose(p_camera->GetMatrixProj());	//プロジェクション変換行列
		cb.matrixView = DirectX::XMMatrixTranspose(p_camera->GetMatrixView());	//ビュー変換行列

		//cb.matrixTex = DirectX::XMMatrixTranspose();
		cb.color = _shape.vertices[0].color;
		cb.matrixTex = DirectX::XMMatrixIdentity();

		// 行列をシェーダーに渡す
		p_DeviceContext->UpdateSubresource(p_constantBuffer, 0, NULL, &cb, 0, 0);
	}

	{
		Sprite2DTextureCB cb;
		cb.isTexture = false;
		p_DeviceContext->UpdateSubresource(p_PSConstantBuffer, 0, NULL, &cb, 0, 0);
	}

	UINT strides = sizeof(Vertex);
	UINT offsets = 0;

	p_DeviceContext->IASetVertexBuffers(0, 1, &(_shape.p_vertexBuffer), &strides, &offsets);
	p_DeviceContext->IASetIndexBuffer(_shape.p_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	p_DeviceContext->DrawIndexed(_shape.indices.size(), 0, 0); // 描画命令
}
