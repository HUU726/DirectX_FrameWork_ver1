#pragma once

#include "../00-IF_Renderer/IF_Renderer.h"
#include "../../998-FH_Types/Vertex.h"
#include "../../998-FH_Types/Sprite2D.h"
#include "../../998-FH_Types/Mesh.h"



class Camera3D;
class MeshFilter;
class SpriteRenderer;
class MeshRenderer;

struct Mesh3DConstBuffer
{
	DirectX::XMFLOAT4 color;
	DirectX::XMMATRIX matrixTex;
	DirectX::XMMATRIX matrixWorld;
	DirectX::XMMATRIX matrixProj;
	DirectX::XMMATRIX matrixView;
};
struct Mesh3DTextureCB
{
	bool isTexture;
};


class Mesh3DRenderer : public IF_Renderer
{
private:

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

	void Draw(const hft::Sprite2D* _sprite);
	void Draw(const hft::Mesh* _mesh);
	void Draw(const MeshFilter* _p_meshFilter);
	void Draw(const SpriteRenderer* _renderer);
	void Draw(const MeshRenderer* _renderer);

};

