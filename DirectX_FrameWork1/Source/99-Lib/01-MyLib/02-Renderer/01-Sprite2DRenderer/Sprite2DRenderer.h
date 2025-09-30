#pragma once
#include "../00-IF_Renderer/IF_Renderer.h"

#include "../../998-FH_Types/Sprite2D.h"



class Camera2D;
class SpriteRenderer;


struct Sprite2DConstBuffer
{
	DirectX::XMFLOAT4 color;
	DirectX::XMMATRIX matrixTex;
	DirectX::XMMATRIX matrixWorld;
	DirectX::XMMATRIX matrixProj;
	DirectX::XMMATRIX matrixView;
};

struct Sprite2DTextureCB
{
	bool isTexture;
};



class Sprite2DRenderer : public IF_Renderer
{
private:

	HRESULT InitShader() override;
	HRESULT InitBuffer() override;
	HRESULT InitState() override;
	void RenderPipeline() override;

	Sprite2DRenderer();

public:
	static Sprite2DRenderer& GetInstance()
	{
		static Sprite2DRenderer instance;
		return instance;
	}

	void SetCamera(Camera2D* _p_camera);

	void Draw(const hft::Sprite2D* _sprite);
	void Draw(const SpriteRenderer* _renderer);

};

