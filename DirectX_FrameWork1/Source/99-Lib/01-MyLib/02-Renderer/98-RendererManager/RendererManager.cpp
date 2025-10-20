/***************************************************************************************************************************
*												マクロ定義
***************************************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

// Direct3D解放の簡略化マクロ
#define SAFE_RELEASE(p) { if( NULL != p ) { p->Release(); p = NULL; } }

/***************************************************************************************************************************
*												インクルード
***************************************************************************************************************************/
#include "RendererManager.h"
#include "../../../../02-App/FH_Window.h"

#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <atltypes.h> // CRectを使うためのヘッダーファイル
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


RendererManager::RendererManager()
{
}


/**
* @brief	DirectX11初期化
* @date		2025/09/04
* @memo		初期化処理全般、授業のやつ流用質問あったら才野先生に聞きにいく
*/
HRESULT RendererManager::Init(HWND _hwnd)
{
	HRESULT hr = S_OK; // HRESULT型→Windowsプログラムで関数実行の成功/失敗を受け取る

	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;                       // バックバッファの数（ダブルバッファ）
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;       // バッファの幅をウィンドウサイズに合わせる
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;     // バッファの高さをウィンドウサイズに合わせる
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // バッファのピクセルフォーマット
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // リフレッシュレートを設定(Hz)
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // バッファの使用用途を設定
	swapChainDesc.OutputWindow = _hwnd;          // スワップチェーンのターゲットウィンドウを設定
	swapChainDesc.SampleDesc.Count = 1;         // マルチサンプリングの設定（アンチエイリアスのサンプル数とクオリティ）
	swapChainDesc.SampleDesc.Quality = 0;       // 同上
	swapChainDesc.Windowed = TRUE;              // ウィンドウモード（フルスクリーンではなく、ウィンドウモードで実行）

	// デバイスとスワップチェインを同時に作成する関数の呼び出し
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE, // ドライバータイプ(ハードウェアGPUを使用)
		NULL,               // ソフトウェアラスタライザを指定しないのでNULL
		0,                  // フラグ（D3D11_CREATE_DEVICE_DEBUGなど） 0は何も指定しない
		NULL,               // 機能レベルの配列。NULLならデフォルトの機能レベルセットが使われる
		0,                  // 機能レベルの配列の要素数(NULLなら0でOK)
		D3D11_SDK_VERSION,  // SDKのバージョン 常に「D3D11_SDK_VERSION」を指定
		&swapChainDesc,     // スワップチェーンの設定構造体へのポインタ
		&this->p_SwapChain,      // 作成されたスワップチェーンを受け取るポインタ
		&this->p_Device,	        // 作成されたデバイスを受け取るポインタ
		&this->featureLevel,    // 作成されたデバイスの機能レベルを受け取る変数へのポインタ
		&this->p_DeviceContext); // 作成されたデバイスコンテキストを受け取るポインタ
	if (FAILED(hr)) return hr;

	// レンダーターゲットビュー作成
	ID3D11Texture2D* renderTarget;
	hr = this->p_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	if (FAILED(hr)) return hr;
	hr = this->p_Device->CreateRenderTargetView(renderTarget, NULL, &this->p_RenderTargetView);
	renderTarget->Release();
	if (FAILED(hr)) return hr;

	// デプスステンシルバッファ作成
	// ※（デプスバッファ = 深度バッファ = Zバッファ）→奥行を判定して前後関係を正しく描画できる
	ID3D11Texture2D* depthStencil{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;   // バッファの幅をスワップチェーンに合わせる
	textureDesc.Height = swapChainDesc.BufferDesc.Height; // バッファの高さをスワップチェーンに合わせる
	textureDesc.MipLevels = 1;                            // ミップレベルは1（ミップマップは使用しない）
	textureDesc.ArraySize = 1;                            // テクスチャの配列サイズ（通常1）
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;           // フォーマットは16ビットの深度バッファを使用
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;    // スワップチェーンと同じサンプル設定
	textureDesc.Usage = D3D11_USAGE_DEFAULT;              // 使用方法はデフォルト（GPUで使用）
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;     // 深度ステンシルバッファとして使用
	textureDesc.CPUAccessFlags = 0;                       // CPUからのアクセスは不要
	textureDesc.MiscFlags = 0;                            // その他のフラグは設定なし
	hr = this->p_Device->CreateTexture2D(&textureDesc, NULL, &depthStencil);
	if (FAILED(hr)) return hr;

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format; // デプスステンシルバッファのフォーマットを設定
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // ビューの次元を2Dテクスチャとして設定（2Dテクスチャ用のデプスステンシルビュー）
	depthStencilViewDesc.Flags = 0; // 特別なフラグは設定しない（デフォルトの動作）
	hr = this->p_Device->CreateDepthStencilView(depthStencil, &depthStencilViewDesc, &this->p_DepthStencilView);
	if (FAILED(hr)) return hr;
	depthStencil->Release();

	// ビューポートを作成（→画面分割などに使う、描画領域の指定のこと）
	CRect rect;
	GetClientRect(_hwnd, &rect);
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)rect.Width();   // ビューポートの幅
	viewport.Height = (FLOAT)rect.Height(); // ビューポートの高さ
	viewport.MinDepth = 0.0f;               // 深度範囲の最小値
	viewport.MaxDepth = 1.0f;               // 深度範囲の最大値
	viewport.TopLeftX = 0;                  // ビューポートの左上隅のX座標
	viewport.TopLeftY = 0;                  // ビューポートの左上隅のY座標
	this->p_DeviceContext->RSSetViewports(1, &viewport);
}

void RendererManager::UnInit()
{
}

void RendererManager::ClearScreen()
{
	// 画面塗りつぶし色
	float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	// 描画先のキャンバスと使用する深度バッファを指定する
	this->p_DeviceContext->OMSetRenderTargets(1, &this->p_RenderTargetView, this->p_DepthStencilView);
	// 描画先キャンバスを塗りつぶす
	this->p_DeviceContext->ClearRenderTargetView(this->p_RenderTargetView, clearColor);
	// 深度バッファをリセットする
	this->p_DeviceContext->ClearDepthStencilView(this->p_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void RendererManager::SwapChain()
{
	// ダブルバッファの切り替えを行い画面を更新する
	this->p_SwapChain->Present(0, 0);
}
