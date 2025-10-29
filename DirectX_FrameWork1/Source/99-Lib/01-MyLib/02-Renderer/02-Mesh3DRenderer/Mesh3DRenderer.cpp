#include "Mesh3DRenderer.h"

#include "../98-RendererManager/RendererManager.h"

#include "../../07-Component/01-Transform/Transform.h"

#include "../../998-FH_Types/TransformMatrix.h"

#include "../../07-Component/04-Camera/02-Camera3D/Camera3D.h"
#include "../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"
#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include "../../06-GameObject/GameObject.h"


Mesh3DRenderer::Mesh3DRenderer()
{
	Init();
}

HRESULT Mesh3DRenderer::InitShader()
{
	HRESULT hr;

	// インプットレイアウト作成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = ARRAYSIZE(layout);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	VS_Path = "Source/99-Lib/01-MyLib/999-Shader/02-3D/01-Mesh3D/VS_Mesh3D.hlsl";
	hr = CreateVertexShader(&this->p_VertexShader, &this->p_InputLayout, layout, numElements, VS_Path);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateVertexShader error", "error", MB_OK);
		return hr;
	}

	// ピクセルシェーダーオブジェクトを生成
	PS_Path = "Source/99-Lib/01-MyLib/999-Shader/02-3D/01-Mesh3D/PS_Mesh3D.hlsl";
	hr = CreatePixelShader(&this->p_PixelShader, PS_Path);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreatePixelShader error", "error", MB_OK);
		return hr;
	}

	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	return S_OK;
}

HRESULT Mesh3DRenderer::InitBuffer()
{

	return S_OK;
}

HRESULT Mesh3DRenderer::InitState()
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
	dsDesc.DepthEnable = TRUE;	//震度テストを有効にする
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	hr = this->p_Device->CreateDepthStencilState(&dsDesc, &this->p_DSState);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void Mesh3DRenderer::SetCamera(Camera3D* _p_camera)
{
	p_camera = _p_camera;
}


void Mesh3DRenderer::Draw(const SpriteRenderer* _rp_enderer)
{
}

void Mesh3DRenderer::Draw(const hft::Polygon* _polygon)
{
}

void Mesh3DRenderer::Draw(MeshRenderer* _p_renderer)
{
	if (p_camera == nullptr)
		return;

	std::shared_ptr<hft::Mesh> shape = _p_renderer->GetShape();
	if (!shape)
		return;

	RenderPipeline();
	p_DeviceContext->DrawIndexed(static_cast<UINT>(shape->indices.size()), 0, 0); // 描画命令
}

void Mesh3DRenderer::Draw(const MeshFilter* _p_meshFilter)
{

}

void Mesh3DRenderer::Draw(const hft::Mesh* _p_mesh)
{
}
