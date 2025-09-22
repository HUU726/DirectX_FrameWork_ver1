#pragma once

#include <DirectXMath.h>

#define PAI (3.141592f)


namespace hft
{

	class TransformMatrix
	{
	public:
		DirectX::XMMATRIX position;
		DirectX::XMMATRIX rotation;
		DirectX::XMMATRIX scale;

		DirectX::XMMATRIX ConversionPosition(DirectX::XMFLOAT4 _pos);
		DirectX::XMMATRIX ConversionRotation(DirectX::XMFLOAT3 _rot);
		DirectX::XMMATRIX ConversionScale(DirectX::XMFLOAT3 _scale);

		DirectX::XMMATRIX GetMatrixWorld();
	};

}