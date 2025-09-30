#pragma once

#include "./HF_FLOAT.h"

#define PAI (3.141592f)


namespace hft
{

	class TransformMatrix
	{
	public:
		DirectX::XMMATRIX position;
		DirectX::XMMATRIX rotation;
		DirectX::XMMATRIX scale;

		DirectX::XMMATRIX ConversionPosition(hft::HFFLOAT4 _pos);
		DirectX::XMMATRIX ConversionRotation(hft::HFFLOAT3 _rot);
		DirectX::XMMATRIX ConversionScale(hft::HFFLOAT3 _scale);

		DirectX::XMMATRIX GetMatrixWorld();
	};

}