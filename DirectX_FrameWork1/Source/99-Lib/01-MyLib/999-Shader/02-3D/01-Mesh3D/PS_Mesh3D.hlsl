#include "../../10-ShaderTypes/ShaderTypes.hlsl"

Texture2D myTexture : register(t0);
SamplerState mySamplerState : register(s0);



float4 main(in PS_IN input) : SV_TARGET
{
    float4 color = input.col;
    
    if (isTexture > 0)
    {
        color *= myTexture.Sample(mySamplerState, input.tex);
    }
    
	return color;
}