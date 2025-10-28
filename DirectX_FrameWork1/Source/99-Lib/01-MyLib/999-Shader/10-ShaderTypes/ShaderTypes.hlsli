// 頂点のデータを表す構造体（受け取り用）
struct VS_IN
{
    float4 pos : POSITION0;
    float4 nrm : NORMAL0;
    float4 col : COLOR0;
    float2 tex : TEXCOORD0;
};

// 頂点のデータを表す構造体（送信用） 
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 tex : TEXCOORD0;
};

// グローバル変数の宣言
// 定数バッファ受け取り用
cbuffer WorldBuffer : register(b0)
{
    matrix matWorld;
}
cbuffer VPBuffer : register(b1)
{
    matrix matView;
    matrix matProj;
}