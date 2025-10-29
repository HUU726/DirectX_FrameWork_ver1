#include "Light.h"



void Light::Init()
{}

void Light::Update()
{}

LightData All_LightData::GetData()
{
    return allData;
}

void All_LightData::SetData(const LightData& _data)
{
    allData.diffuse = _data.diffuse;
}
