//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
#include "../10-ShaderTypes/ShaderTypes.hlsli"

 
// 頂点シェーダーのエントリポイント 
PS_IN main(VS_IN input)
{
    PS_IN output;
 
    matrix wvp;
    wvp = mul(matWorld, matView);
    wvp = mul(wvp, matProj);
   
    output.pos = mul(input.pos, wvp);
    output.tex = input.tex;
    output.col = input.col;
    
    return output;
}