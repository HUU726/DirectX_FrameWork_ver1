//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
#include "../../10-ShaderTypes/ShaderTypes.hlsli"

 
// 頂点シェーダーのエントリポイント 
PS_IN main(in VS_IN input)
{
    PS_IN output;
    
    matrix wp;
    wp = mul(matWorld, matProj);
    
    output.pos = mul(input.pos, wp);
    output.tex = input.tex;
    output.col = input.col;
    
    return output;
}