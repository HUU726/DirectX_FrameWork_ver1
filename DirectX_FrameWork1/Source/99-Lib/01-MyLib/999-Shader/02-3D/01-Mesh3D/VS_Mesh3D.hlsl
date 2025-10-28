#include "../../10-ShaderTypes/ShaderTypes.hlsl"


PS_IN main(in VS_IN input)
{
    PS_IN output;
    
    matrix wvp;
    wvp = mul(matrixWorld, matrixView);
    wvp = mul(wvp, matrixProjction);
    
    output.pos = mul(input.pos, wvp);
    output.tex = input.tex;
    output.col = input.col;
    
	return output;
}