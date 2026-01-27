#include "Sprite2DRenderer.h"


#include "../../998-FH_Types/Sprite2D.h"
#include "../../07-Component/04-Camera/01-Camera2D/Camera2D.h"
#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"


#define VERTEX_NUM_2D (4)



Sprite2DRenderer::Sprite2DRenderer()
{
	Init();
}

/**
* @brief	デフォルトのシェーダーを初期化
*/
HRESULT Sprite2DRenderer::InitDefaultShader()
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
	hr = ::CreateVertexShader(&this->p_defaultVertexShader, &this->p_InputLayout, layouts.data(), layouts.size(), VS_Path);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateVertexShader error", "error", MB_OK);
		return hr;
	}

	// ピクセルシェーダーオブジェクトを生成
	PS_Path = "Source/99-Lib/01-MyLib/999-Shader/01-2D/01-Sprite2DShader/PS_Sprite2D.hlsl";
	hr = ::CreatePixelShader(&this->p_defaultPixelShader, PS_Path);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreatePixelShader error", "error", MB_OK);
		return hr;
	}

	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	return S_OK;
}

HRESULT Sprite2DRenderer::InitBuffer()
{
	return S_OK;
}

/**
* @brief	ステートを初期化
* @note		描画に使う設計図を設定
*/
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
	//rasterizerDesc.CullMode = D3D11_CULL_BACK; //ポリゴン裏をカリング
	//rasterizerDesc.CullMode = D3D11_CULL_FRONT; //ポリゴン表をカリング
	rasterizerDesc.CullMode = D3D11_CULL_NONE; //カリングしない(裏も表も表示される)
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;
	hr = p_Device->CreateRasterizerState(&rasterizerDesc, &p_RRState);
	if (FAILED(hr)) return hr;
	p_DeviceContext->RSSetState(p_RRState);

	//デプスステンシルステート作成
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.DepthEnable = FALSE;	//震度テストを有効にする
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	hr = this->p_Device->CreateDepthStencilState(&dsDesc, &this->p_DSState);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void Sprite2DRenderer::SetCamera(Camera2D* _p_camera)
{
	p_camera = _p_camera;
}

void Sprite2DRenderer::Draw(const hft::Sprite2D* _sprite)
{

	if (p_camera == nullptr)
		return;

	RenderPipeline();

	UINT strides = sizeof(hft::Vertex);
	UINT offsets = 0;

	p_DeviceContext->DrawIndexed(_sprite->indices.size(),0 , 0); // 描画命令
}

void Sprite2DRenderer::Draw(SpriteRenderer* _p_renderer)
{

	if (p_camera == nullptr)
		return;

	std::shared_ptr<hft::Polygon> shape = _p_renderer->GetShape();
	if (!shape)
		return;

	hft::Polygon& polygon = _p_renderer->GetPolygonRef();

	RenderPipeline();
	SetMaterial(polygon.material);

	//p_DeviceContext->DrawIndexed(static_cast<UINT>(shape->indices.size()), 0, 0); // 描画命令
	p_DeviceContext->DrawIndexed(static_cast<UINT>(polygon.indices.size()), 0, 0); // 描画命令
}

void Sprite2DRenderer::Draw(const hft::Polygon& _shape, hft::HFFLOAT4 _pos, hft::HFFLOAT3 _scl, hft::HFFLOAT3 _rot)
{
	if (p_camera == nullptr)
		return;

	RenderPipeline();

	hft::TransformMatrix mtrxTf;
	mtrxTf.ConversionPosition(_pos);
	mtrxTf.ConversionRotation(_rot);
	mtrxTf.ConversionScale(_scl);


	p_DeviceContext->DrawIndexed(_shape.indices.size(), 0, 0); // 描画命令
}
