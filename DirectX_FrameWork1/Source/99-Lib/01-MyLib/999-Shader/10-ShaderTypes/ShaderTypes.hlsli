// 頂点のデータを表す構造体
struct VS_IN
{
    float4 pos : POSITION0;
    float4 nrm : NORMAL0;
    float4 col : COLOR0;
    float2 tex : TEXCOORD0;
};

// 頂点のデータを表す構造体
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
cbuffer ConstBuffer : register(b2)
{
    int isTexture;
}


struct LIGHT
{
    bool enable;        //使用するか否か
    bool3 fake;         //余白
    float4 direction;   //平行光源の方向
    float4 diffuse;     //拡散反射用の光の強さ
    float4 ambient;     //環境光用の光の強さ
};

cbuffer LightBuffer : register(b3)
{
    LIGHT light;
}

struct Material
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emission;
    float shininess;
    int isTexture;
};

cbuffer MaterialBuffer : register(b4)
{
    Material material;
}


cbuffer TexBuffer : register(b6)
{
    matrix matTex;
}