#include "TransformMatrix.h"

DirectX::XMMATRIX hft::TransformMatrix::ConversionPosition(hft::HFFLOAT4 _pos)
{
	matPosition = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
    return matPosition;
}

DirectX::XMMATRIX hft::TransformMatrix::ConversionRotation(hft::HFFLOAT3 _rot)
{
	float pitch = DirectX::XMConvertToRadians(_rot.x);
	float yaw = DirectX::XMConvertToRadians(_rot.y);
	float roll = DirectX::XMConvertToRadians(_rot.z);
	matRotation = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
    return matRotation;
}

DirectX::XMMATRIX hft::TransformMatrix::ConversionScale(hft::HFFLOAT3 _scl)
{
	matScale = DirectX::XMMatrixScaling(_scl.x, _scl.y, _scl.z);
    return matScale;
}

DirectX::XMMATRIX hft::TransformMatrix::GetMatrixWorld()
{
	// ワールド行列　＝　スケーリング行列　×　回転行列　×　平行移動行列
    return (matScale * matRotation * matPosition);
}
