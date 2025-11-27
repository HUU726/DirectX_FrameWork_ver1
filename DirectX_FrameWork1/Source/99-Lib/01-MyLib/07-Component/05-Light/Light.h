#pragma once

#include "../00-Component/Component.h"
#include "../../998-FH_Types/HF_FLOAT.h"


struct LightData
{
	bool enable;
	bool fake[3];
	DirectX::XMVECTOR direction;	//平行光源の方向
	hft::HFFLOAT4 diffuse;		//平行光源の強さと色(RGBA = XYZW)
	hft::HFFLOAT4 ambent;		//環境光源の強さと色(RGBA = XYZW)
};

class Light : public Component
{
private:
	LightData data;

public:
	void Init() override;
	void Update() override;
	void Action() override;
};


class All_LightData
{
private:
	LightData allData;
	All_LightData();

public:
	LightData GetData();
	void SetData(const LightData& _data);

};
