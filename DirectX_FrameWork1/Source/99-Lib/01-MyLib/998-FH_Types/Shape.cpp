#include "Shape.h"
#include "../02-Renderer/98-RendererManager/RendererManager.h"


HRESULT hft::CreateVertexBuffer(std::shared_ptr<Shape> _sp_shape)
{
	RendererManager& rendererMng = RendererManager::GetInstance();
	HRESULT hr;

	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(vbDesc));
	vbDesc.Usage = D3D11_USAGE_DEFAULT;
	vbDesc.ByteWidth = sizeof(hft::Vertex) * _sp_shape->vertices.size();
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = (void*)_sp_shape->vertices.data();

	hr = rendererMng.GetDevice()->CreateBuffer(&vbDesc, &initData, &_sp_shape->p_vertexBuffer);
	if (FAILED(hr)) {
		MessageBoxA(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return hr;
	}

	return S_OK;
}

HRESULT hft::CreateVertexIndexBuffer(std::shared_ptr<Shape> _sp_shape)
{
	RendererManager& rendererMng = RendererManager::GetInstance();
	HRESULT hr;

	{
		D3D11_BUFFER_DESC vbDesc;
		ZeroMemory(&vbDesc, sizeof(vbDesc));
		vbDesc.Usage = D3D11_USAGE_DEFAULT;
		vbDesc.ByteWidth = sizeof(hft::Vertex) * _sp_shape->vertices.size();
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));
		initData.pSysMem = (void*)_sp_shape->vertices.data();

		hr = rendererMng.GetDevice()->CreateBuffer(&vbDesc, &initData, &_sp_shape->p_vertexBuffer);
		if (FAILED(hr)) {
			MessageBoxA(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
			return hr;
		}
	}


	{
		D3D11_BUFFER_DESC ibDesc;
		ZeroMemory(&ibDesc, sizeof(ibDesc));
		ibDesc.Usage = D3D11_USAGE_DEFAULT;
		ibDesc.ByteWidth = sizeof(unsigned int) * _sp_shape->indices.size();
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));
		initData.pSysMem = (void*)_sp_shape->indices.data();

		hr = rendererMng.GetDevice()->CreateBuffer(&ibDesc, &initData, &_sp_shape->p_indexBuffer);
		if (FAILED(hr)) {
			MessageBoxA(nullptr, "CreateBuffer(index buffer) error", "Error", MB_OK);
			return hr;
		}
	}

	return S_OK;

}
