#pragma once

#include "../00-IF_Renderer/IF_Renderer.h"
#include "../../998-FH_Types/Vertex.h"
#include "../../998-FH_Types/Polygon.h"
#include "../../998-FH_Types/Mesh.h"



class Camera3D;
class MeshFilter;
class SpriteRenderer;
class MeshRenderer;

struct VS_CB_Mesh3D
{
	DirectX::XMFLOAT4 color;
	DirectX::XMMATRIX matrixTex;
	DirectX::XMMATRIX matrixWorld;
	DirectX::XMMATRIX matrixProj;
	DirectX::XMMATRIX matrixView;
};
struct PS_CB_Mesh3D
{
	bool isTexture;
};


class Mesh3DRenderer : public IF_Renderer
{
private:
	ID3D11Buffer* p_PSConstantBuffer;

	HRESULT InitShader() override;
	HRESULT InitBuffer() override;
	HRESULT InitState() override;
	void RenderPipeline() override;

	Mesh3DRenderer();

public:
	static Mesh3DRenderer& GetInstance()
	{
		static Mesh3DRenderer instance;
		return instance;
	}

	void SetCamera(Camera3D* _p_camera);

	void Draw(const hft::Polygon* _p_polygon);
	void Draw(const SpriteRenderer* _p_renderer);
	void Draw(MeshRenderer* _p_renderer);
	void Draw(const MeshFilter* _p_meshFilter);
	void Draw(const hft::Mesh* _p_mesh);
};

