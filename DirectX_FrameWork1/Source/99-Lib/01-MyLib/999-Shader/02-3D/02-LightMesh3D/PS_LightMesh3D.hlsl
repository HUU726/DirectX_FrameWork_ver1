#include "../../10-ShaderTypes/ShaderTypes.hlsli"

Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

float4 main(in PS_IN input)  : SV_Target
{	
    float4 color = input.col;

    if (material.isTexture)
    {
        color = color * myTexture.Sample(mySampler, input.tex);
    }
    else
    {
        color = color * material.diffuse;
    }


    return color;
}

