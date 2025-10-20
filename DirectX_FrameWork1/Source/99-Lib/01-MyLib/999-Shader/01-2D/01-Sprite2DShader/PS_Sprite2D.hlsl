//--------------------------------------------------------------------------------------
// ピクセルシェーダー
//--------------------------------------------------------------------------------------

// ピクセルの情報の構造体（受け取り用）
struct PS_IN
{
    // float4型　→　float型が４つの構造体
    float4 pos : SV_POSITION; // ピクセルの画面上の座標
    float4 col : COLOR0;
    float2 tex : TEXCOORD;
};
// グローバル変数の宣言
// ※C言語側からデータを渡されたときにセットされる変数
Texture2D myTexture : register(t0); //テクスチャー
SamplerState mySampler : register(s0); //サンプラー
// 定数バッファ受け取り用
cbuffer ConstBuffer : register(b0)
{
    int isTexture;
}

// ピクセルシェーダーのエントリポイント
float4 main(PS_IN input) : SV_Target
{
    float4 color = input.col;
    
    if (isTexture > 0)
    {
        color = color * myTexture.Sample(mySampler, input.tex);
    }
    
    // 決定した色をreturnする
    return color;
}
