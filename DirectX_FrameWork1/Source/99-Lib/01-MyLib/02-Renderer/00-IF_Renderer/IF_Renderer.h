#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

class IF_Camera;


class IF_Renderer
{
protected:
	ID3D11InputLayout* p_InputLayout;	// インプットレイアウト
	ID3D11VertexShader* p_VertexShader;	// 頂点シェーダーオブジェクト
	ID3D11PixelShader* p_PixelShader;	// ピクセルシェーダーオブジェクト
	ID3D11Buffer* p_constantBuffer;		// 定数バッファ用変数
	D3D_PRIMITIVE_TOPOLOGY topology;	// 頂点の結び方(とらえ方)

	ID3D11Buffer* p_vertexBuffer;		//頂点バッファー
	ID3D11Buffer* p_indexBuffer;		//インデックスバッファー

	ID3D11SamplerState* p_Sampler;		// サンプラー用変数
	ID3D11BlendState* p_BlendState;		// ブレンドステート用変数(αブレンディング)
	ID3D11DepthStencilState* p_DSState;	// Z軸に対して同描画するかなどなど

	IF_Camera* p_camera;

	DirectX::XMMATRIX matrixProj;		//プロジェクション変換行列
	DirectX::XMMATRIX matrixWarld;		//ワールド変換行列
	DirectX::XMMATRIX matrixView;		//ビュー変換行列

	/************************  Systemクラスからポインタをもらう  ****************************************************************/
	ID3D11Device* p_Device;						// デバイス＝DirectXの各種機能を作る
	ID3D11DeviceContext* p_DeviceContext;		// コンテキスト＝描画関連を司る機能
	IDXGISwapChain* p_SwapChain;				// スワップチェイン＝ダブルバッファ機能
	ID3D11RenderTargetView* p_RenderTargetView;	// レンダーターゲット＝描画先を表す機能
	ID3D11DepthStencilView* p_DepthStencilView;	// デプスステンシルビュー(もらはなくてもいい)
	/****************************************************************************************************************************/


	HRESULT CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ppShaderObject, int* pShaderObjectSize);
	HRESULT CreateVertexShader(ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout, D3D11_INPUT_ELEMENT_DESC* pLayout, unsigned int numElements, const char* szFileName);
	HRESULT CreatePixelShader(ID3D11PixelShader** ppPixelShader, const char* szFileName);

	virtual HRESULT InitShader() = 0;	//レイアウト・シェーダー・定数バッファの初期化
	virtual HRESULT InitBuffer() = 0;		//頂点バッファを初期化
	virtual HRESULT InitState() = 0;	//サンプラー・ブレンドステート・深度の初期化
	virtual void RenderPipeline() = 0;
	void Init();

	IF_Renderer();

public:

};

