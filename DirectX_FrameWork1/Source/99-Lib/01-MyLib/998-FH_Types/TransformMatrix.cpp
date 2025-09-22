#include "TransformMatrix.h"

DirectX::XMMATRIX hft::TransformMatrix::ConversionPosition(DirectX::XMFLOAT4 _pos)
{
    return this->position = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);;
}

DirectX::XMMATRIX hft::TransformMatrix::ConversionRotation(DirectX::XMFLOAT3 _rot)
{
    return rotation = DirectX::XMMatrixRotationRollPitchYaw(_rot.x, _rot.y, _rot.z);
}

DirectX::XMMATRIX hft::TransformMatrix::ConversionScale(DirectX::XMFLOAT3 _scl)
{
    return this->scale = DirectX::XMMatrixScaling(_scl.x, _scl.y, _scl.z);
}

DirectX::XMMATRIX hft::TransformMatrix::GetMatrixWorld()
{
    return (this->scale * this->rotation * this->position);
}
