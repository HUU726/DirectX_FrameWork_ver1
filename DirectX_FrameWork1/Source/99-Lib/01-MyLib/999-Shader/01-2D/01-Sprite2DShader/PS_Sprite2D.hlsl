//--------------------------------------------------------------------------------------
// ピクセルシェーダー
//--------------------------------------------------------------------------------------
#include "../../10-ShaderTypes/ShaderTypes.hlsli"

// グローバル変数の宣言
// ※C言語側からデータを渡されたときにセットされる変数
Texture2D myTexture : register(t0); //テクスチャー
SamplerState mySampler : register(s0); //サンプラー



// ピクセルシェーダーのエントリポイント
float4 main(in PS_IN input) : SV_Target
{
    float4 color = input.col;
    
    if (material.isTexture > 0)
    {
        float4 uv;
        uv.xy = input.tex;
        uv.z = 0.0f;
        uv.w = 1.0f;
        input.tex = mul(uv, matTex);
        
        color = color * myTexture.Sample(mySampler, input.tex);
    }
    
    // 決定した色をreturnする
    return color;
}
