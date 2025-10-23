#pragma once
#include "../00-IF_Renderer/IF_Renderer.h"

#include "../../998-FH_Types/Sprite2D.h"
#include "../../998-FH_Types/Polygon.h"



class Camera2D;
class SpriteRenderer;


struct VS_CB_Sprite2D
{
	DirectX::XMFLOAT4 color;
	DirectX::XMMATRIX matrixTex;
	DirectX::XMMATRIX matrixWorld;
	DirectX::XMMATRIX matrixProj;
	DirectX::XMMATRIX matrixView;
};

struct PS_CB_Sprite2D
{
	int isTexture;
};



class Sprite2DRenderer : public IF_Renderer
{
private:
	ID3D11Buffer* p_PSConstantBuffer;		// ピクセルシェーダー用定数バッファ用変数

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
	void Draw(SpriteRenderer* _renderer);
	void Draw(const hft::Polygon& _shape, hft::HFFLOAT4 _pos = { 0.f,0.f,0.f,0.f }, hft::HFFLOAT3 _scl = { 100.f,100.f,0.f }, hft::HFFLOAT3 _rot = { 0.f,0.f,0.f });

};

