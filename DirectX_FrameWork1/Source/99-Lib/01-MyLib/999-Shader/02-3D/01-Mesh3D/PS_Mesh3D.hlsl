<<<<<<< HEAD
//--------------------------------------------------------------------------------------
// ピクセルシェーダー
//--------------------------------------------------------------------------------------
#include "../../10-ShaderTypes/ShaderTypes.hlsli"

// グローバル変数の宣言
// ※C言語側からデータを渡されたときにセットされる変数
Texture2D myTexture : register(t0); //テクスチャー
SamplerState mySampler : register(s0); //サンプラー
// 定数バッファ受け取り用
cbuffer ConstBuffer : register(b2)
{
    int isTexture;
}

// ピクセルシェーダーのエントリポイント
float4 main(PS_IN input) : SV_Target
{
=======
#include "../../10-ShaderTypes/ShaderTypes.hlsl"

Texture2D myTexture : register(t0);
SamplerState mySamplerState : register(s0);



float4 main(in PS_IN input) : SV_TARGET
{
>>>>>>> 4e40d2ad3e76ecdcf30e95654a22433b59b29bb2
    float4 color = input.col;
    
    if (isTexture > 0)
    {
<<<<<<< HEAD
        color = color * myTexture.Sample(mySampler, input.tex);
    }
    
    // 決定した色をreturnする
    return color;
}
=======
        color *= myTexture.Sample(mySamplerState, input.tex);
    }
    
	return color;
}
>>>>>>> 4e40d2ad3e76ecdcf30e95654a22433b59b29bb2
