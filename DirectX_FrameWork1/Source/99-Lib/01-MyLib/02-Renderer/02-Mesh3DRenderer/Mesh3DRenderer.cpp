#include "Mesh3DRenderer.h"

#include "../98-RendererManager/RendererManager.h"

#include "../../07-Component/01-Transform/Transform.h"

#include "../../998-FH_Types/TransformMatrix.h"

#include "../../07-Component/04-Camera/01-Camera2D/Camera2D.h"
#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

using hft::Vertex;
using hft::Sprite2D;
using hft::TransformMatrix;

Mesh3DRenderer::Mesh3DRenderer()
{
	Init();
}

HRESULT Mesh3DRenderer::InitShader()
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
	cdDesc.ByteWidth = sizeof(Mesh3DConstBuffer);
	cdDesc.Usage = D3D11_USAGE_DEFAULT;
	cdDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cdDesc.CPUAccessFlags = 0;
	cdDesc.MiscFlags = 0;
	cdDesc.StructureByteStride = 0;
	hr = this->p_Device->CreateBuffer(&cdDesc, NULL, &this->p_constantBuffer);
	if (FAILED(hr)) return hr;

	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	return S_OK;
}

HRESULT Mesh3DRenderer::InitBuffer()
{
	HRESULT hr;

	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.Usage = D3D11_USAGE_DYNAMIC;
	vbDesc.ByteWidth = sizeof(Vertex);// * VERTEX_NUM_2D;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	hr = this->p_Device->CreateBuffer(&vbDesc, nullptr, &this->p_vertexBuffer); // 初期データなし
	if (FAILED(hr)) return hr;

	D3D11_BUFFER_DESC ibDesc = {};
	ibDesc.Usage = D3D11_USAGE_DYNAMIC;
	ibDesc.ByteWidth = sizeof(unsigned int);// * VERTEX_NUM_2D;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	hr = this->p_Device->CreateBuffer(&ibDesc, nullptr, &this->p_indexBuffer);

	return S_OK;
}

HRESULT Mesh3DRenderer::InitState()
{
	return E_NOTIMPL;
}

void Mesh3DRenderer::RenderPipeline()
{
}

void Mesh3DRenderer::SetCamera(Camera3D* _p_camera)
{
}

void Mesh3DRenderer::Draw(const hft::Sprite2D* _p_sprite)
{
}

void Mesh3DRenderer::Draw(const hft::Mesh* _p_mesh)
{
}

void Mesh3DRenderer::Draw(const MeshFilter* _p_meshFilter)
{
}

void Mesh3DRenderer::Draw(const SpriteRenderer* _rp_enderer)
{
}

void Mesh3DRenderer::Draw(const MeshRenderer* _p_renderer)
{
}
