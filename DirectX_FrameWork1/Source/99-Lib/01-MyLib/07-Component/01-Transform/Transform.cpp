#include "Transform.h"

void Transform::Init()
{
    Forward();
}

void Transform::Update()
{
    Forward();
}


hft::HFFLOAT3 Transform::Forward()
{
    using namespace DirectX;
   
    hft::HFFLOAT3 rot = rotation;
    rot.x = XMConvertToRadians(rot.x);
    rot.y = XMConvertToRadians(rot.y);
    rot.z = XMConvertToRadians(rot.z);
    XMMATRIX matRotation = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);

    XMVECTOR defaultForward = XMVectorSet(0.f, 0.f, 1.f, 0.f);
    XMVECTOR forwardDir = XMVector3TransformNormal(defaultForward, matRotation);
    forwardDir = XMVector3Normalize(forwardDir);

    hft::HFFLOAT3 forward;
    XMStoreFloat3(&forward, forwardDir);

    return forward;
}

hft::HFFLOAT3 Transform::Right()
{
    using namespace DirectX;

    hft::HFFLOAT3 rot = rotation;
    rot.x = XMConvertToRadians(rot.x);
    rot.y = XMConvertToRadians(rot.y);
    rot.z = XMConvertToRadians(rot.z);
    XMMATRIX matRotation = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);

    XMVECTOR defaultUp = XMVectorSet(1.f, 0.f, 0.f, 0.f);
    XMVECTOR upDir = XMVector3TransformNormal(defaultUp, matRotation);
    upDir = XMVector3Normalize(upDir);

    hft::HFFLOAT3 up;
    XMStoreFloat3(&up, upDir);

    return up;
}

hft::HFFLOAT3 Transform::Up()
{
    using namespace DirectX;

    hft::HFFLOAT3 rot = rotation;
    rot.x = XMConvertToRadians(rot.x);
    rot.y = XMConvertToRadians(rot.y);
    rot.z = XMConvertToRadians(rot.z);
    XMMATRIX matRotation = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);

    XMVECTOR defaultRight = XMVectorSet(0.f, 1.f, 0.f, 0.f);
    XMVECTOR rightDir = XMVector3TransformNormal(defaultRight, matRotation);
    rightDir = XMVector3Normalize(rightDir);

    hft::HFFLOAT3 right;
    XMStoreFloat3(&right, rightDir);

    return right;
}
