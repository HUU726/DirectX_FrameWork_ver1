#include "TransformMatrix.h"

DirectX::XMMATRIX hft::TransformMatrix::ConversionPosition(hft::HFFLOAT4 _pos)
{
    return this->position = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);;
}

DirectX::XMMATRIX hft::TransformMatrix::ConversionRotation(hft::HFFLOAT3 _rot)
{
    return rotation = DirectX::XMMatrixRotationRollPitchYaw(_rot.x, _rot.y, _rot.z);
}

DirectX::XMMATRIX hft::TransformMatrix::ConversionScale(hft::HFFLOAT3 _scl)
{
    return this->scale = DirectX::XMMatrixScaling(_scl.x, _scl.y, _scl.z);
}

DirectX::XMMATRIX hft::TransformMatrix::GetMatrixWorld()
{
    return (this->scale * this->rotation * this->position);
}
