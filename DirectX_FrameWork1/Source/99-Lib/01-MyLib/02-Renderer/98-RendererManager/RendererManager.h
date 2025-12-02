#pragma once

#include <d3d11.h>

class RendererManager
{
private:
	D3D_FEATURE_LEVEL featureLevel;	//Direct3Dバージョン

	ID3D11Device* p_Device;			// デバイス＝DirectXの各種機能を作る ※ID3D11で始まるポインタ型の変数は、解放する必要がある
	ID3D11DeviceContext* p_DeviceContext;	// コンテキスト＝描画関連を司る機能
	IDXGISwapChain* p_SwapChain;		// スワップチェイン＝ダブルバッファ機能
	ID3D11RenderTargetView* p_RenderTargetView;	// レンダーターゲット＝描画先を表す機能
	ID3D11DepthStencilView* p_DepthStencilView;	// デプスバッファ


	RendererManager();

public:
	static RendererManager& GetInstance()
	{
		static RendererManager instance;
		return instance;
	}

	/*** ゲッター ***/
	ID3D11Device* GetDevice() const { return p_Device; }
	ID3D11DeviceContext* GetDeviceContext() const { return p_DeviceContext; }

	HRESULT Init(HWND _hwnd);
	void UnInit();

	void ClearScreen();	//画面クリア
	void SwapChain();	//スワップチェイン

};

