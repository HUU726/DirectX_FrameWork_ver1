//--------------------------------------------------------------------------------------
// ピクセルシェーダー
//--------------------------------------------------------------------------------------
#include "../10-ShaderTypes/ShaderTypes.hlsli"

// グローバル変数の宣言
// ※C言語側からデータを渡されたときにセットされる変数
Texture2D myTexture : register(t0); //テクスチャー
SamplerState mySampler : register(s0); //サンプラー



// ピクセルシェーダーのエントリポイント
float4 main(PS_IN input) : SV_Target
{
    float4 color = input.col;
    color = color * material.diffuse;
    
    if (material.isTexture > 0)
    {
        color = color * myTexture.Sample(mySampler, input.tex);
    }
    //else
    //{
    //    color = color * material.diffuse;
    //}

    return color;
}