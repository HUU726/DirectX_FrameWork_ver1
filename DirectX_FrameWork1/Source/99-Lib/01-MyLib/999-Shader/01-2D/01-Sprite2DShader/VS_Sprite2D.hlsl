//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
#include "../../10-ShaderTypes/ShaderTypes.hlsli"

 
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
  
    output.col = input.col;
    
    return output;
}