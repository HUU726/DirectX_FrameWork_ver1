//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
#include "../../10-ShaderTypes/ShaderTypes.hlsli"

<<<<<<< HEAD
 
// 頂点シェーダーのエントリポイント 
PS_IN main(VS_IN input)
{
    PS_IN output;
 
    // ワールド変換行列を頂点座標に掛けて、移動、回転、拡大縮小する
    output.pos = mul(input.pos, matWorld);
    // ビュー変換行列をかけて、カメラの位置を反映させる
    output.pos = mul(output.pos, matView);
    // 頂点座標に投影行列をかけて、平面上の座標にする
    output.pos = mul(output.pos, matProj);
    
    output.tex = input.tex;
  
=======
#include "../../10-ShaderTypes/ShaderTypes.hlsl"
 
// 頂点シェーダーのエントリポイント 
PS_IN main(in VS_IN input)
{
    PS_IN output;
    
    matrix wvp;
    wvp = mul(matrixWorld, matrixView);
    wvp = mul(wvp, matrixProjction);
    
    output.pos = mul(input.pos, wvp);
    output.tex = input.tex;
>>>>>>> 4e40d2ad3e76ecdcf30e95654a22433b59b29bb2
    output.col = input.col;
    
    return output;
}