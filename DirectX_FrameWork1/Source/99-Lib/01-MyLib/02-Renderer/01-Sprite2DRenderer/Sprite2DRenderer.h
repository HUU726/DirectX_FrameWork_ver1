#pragma once
#include "../00-IF_Renderer/IF_Renderer.h"

#include "../../998-FH_Types/Sprite2D.h"


struct Sprite2DConstBuffer
{
	DirectX::XMFLOAT4 color;
	DirectX::XMMATRIX matrixTex;
	DirectX::XMMATRIX matrixWorld;
	DirectX::XMMATRIX matrixProj;
	DirectX::XMMATRIX matrixView;
};



class Sprite2DRenderer : public IF_Renderer
{
private:
	HRESULT InitShader() override;
	HRESULT InitBuffer() override;
	HRESULT InitState() override;
	void Init();
	void RenderPipeline() override;

	Sprite2DRenderer();

public:
	static Sprite2DRenderer& GetInstance()
	{
		static Sprite2DRenderer instance;
		return instance;
	}

	void Draw(const Sprite2D* _sprite);

};

