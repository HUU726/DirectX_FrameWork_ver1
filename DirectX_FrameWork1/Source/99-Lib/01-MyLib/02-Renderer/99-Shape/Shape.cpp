#include "Shape.h"
#include "../01-Sprite2DRenderer/Sprite2DRenderer.h"
#include "../../01-System/System.h"


void CreateVertexIndexBuffer(std::shared_ptr<Shape2D> _sp_shape)
{
	Sprite2DRenderer& renderer = Sprite2DRenderer::GetInstance();
	RendererManager& system = RendererManager::GetInstance();
	HRESULT hr;

	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.Usage = D3D11_USAGE_DYNAMIC;
	vbDesc.ByteWidth = sizeof(hft::Vertex) * _sp_shape->vertices.size();
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	system.GetDevice()->CreateBuffer(&vbDesc, nullptr, &_sp_shape->p_vertexBuffer); // ‰Šúƒf[ƒ^‚È‚µ


	D3D11_BUFFER_DESC ibDesc = {};
	ibDesc.Usage = D3D11_USAGE_DYNAMIC;
	ibDesc.ByteWidth = sizeof(unsigned int) * _sp_shape->indices.size();
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	hr = system.GetDevice()->CreateBuffer(&ibDesc, nullptr, &_sp_shape->p_indexBuffer);
}
