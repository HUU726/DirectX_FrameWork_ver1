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
    //法線ベクトルの変換と正規化を行う
    //入力された法線をワールド空間に変換し、正規化する
    float4 normal = float4(input.nrm.xyz, 0.0); //入力法線をfloat4に変換
    float4 worldNormal = mul(normal, matWorld); //法線をワールド空間に変換
    worldNormal = normalize(worldNormal);       //法線ベクトルを正規化
    
    //光源邦コント法線ベクトルのない席を計算して拡散光を求める
    float d = -dot(light.direction.xyz, worldNormal.xyz);
    
    d = saturate(d);    //dの値を0~1にクランプ
    
    output.col.xyz = input.col.xyz * d * light.diffuse.xyz; // 拡散光の影響を乗算
    output.col.xyz += input.col.xyz * light.ambient.xyz; // アンビエント光を加算
    output.col.a = input.col.a; // アルファ値はそのまま使用
	
	//texture=============================
	// テクスチャ座標はそのまま使用
    output.tex = input.tex;
	
    return output;
}

