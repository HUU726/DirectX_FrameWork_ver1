#include "../../10-ShaderTypes/ShaderTypes.hlsli"

PS_IN main(in VS_IN input)
{
    PS_IN output;

	//positoin=============================
	// ワールド、ビュー、プロジェクション行列を掛け合わせて座標変換を行う
	matrix wvp;
	wvp = mul(matWorld, matView);
	wvp = mul(wvp, matProj);
    output.pos = mul(input.pos, wvp);

	//color=============================
    output.col.xyz = input.col.xyz * light.diffuse.xyz; // 拡散光の影響を乗算
    output.col.xyz += input.col.xyz * light.ambient.xyz; // アンビエント光を加算
    output.col.a = input.col.a; // アルファ値はそのまま使用
	
	//texture=============================
	// テクスチャ座標はそのまま使用
    output.tex = input.tex;
	
    return output;
}

