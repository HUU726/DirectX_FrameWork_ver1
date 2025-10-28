struct VS_IN
{
    float4 pos : POSITION0;
    float4 nrm : NORMAL0;
    float4 col : COLOR0;
    float2 tex : TEXCOORD0;
};
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 tex : TEXCOORD0;
};



cbuffer WorldBuffer : register(b0)
{
    matrix matrixWorld;
};
cbuffer VPBuffer : register(b1)
{
    matrix matrixView;
    matrix matrixProjction;
};
cbuffer TextureBuffer : register(b2)
{
    int isTexture;
};

struct LIGHT
{
    int enable; //使用するか否か
    float4 direction; //平行光源の方向
    float4 diffuse; //拡散反射用の光の強さ
    float4 ambient; //環境光用の光の強さ
};

cbuffer LightBuffer : register(b3)
{
    LIGHT light;
};