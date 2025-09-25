#include "Camera.h"

#include "../../06-GameObject/GameObject.h"


enum VIEW_ELEMENT
{
	CAMERA_POS = 0,
	TARGET_POS,
	UP_DIRECT,
	ALL_ELEMENT,
};

std::vector<DirectX::XMVECTOR> Camera::DeriveTargetToForward()
{
	std::vector<DirectX::XMVECTOR> ansVector;
	ansVector.resize(ALL_ELEMENT);

	Transform* l_transform = GetGameObject()->GetTransformPtr();
	auto pos = l_transform->position;
	auto rot = l_transform->rotation;
	DirectX::XMVECTOR cameraPos = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.f);		//カメラの位置

	DirectX::XMVECTOR targetPos = DirectX::XMVectorSet(p_targetPos->x, p_targetPos->y, p_targetPos->z, 0.f);	//ターゲットの位置

	auto forwardDirect = DirectX::XMVectorSubtract(targetPos, cameraPos);	//前方向
	forwardDirect = DirectX::XMVector3Normalize(forwardDirect);	//正規化



	return std::vector<DirectX::XMVECTOR>();
}

std::vector<DirectX::XMVECTOR> Camera::DeriveForwardToTarget()
{
	std::vector<DirectX::XMVECTOR> ansVector;
	ansVector.resize(ALL_ELEMENT);

	Transform* l_transform = GetGameObject()->GetTransformPtr();
	auto pos = l_transform->position;
	auto rot = l_transform->rotation;
	DirectX::XMVECTOR cameraPos = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f);		//カメラの位置

	DirectX::XMVECTOR defaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);	//初期前方向
	DirectX::XMVECTOR defaultUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);			//初期上方向
	DirectX::XMMATRIX matrixRot = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);	//カメラの回転情報


	DirectX::XMVECTOR forwardDirect = DirectX::XMVector3TransformNormal(defaultForward, matrixRot);	//前方向
	forwardDirect = DirectX::XMVector3Normalize(forwardDirect);	//正規化

	DirectX::XMVECTOR upDirect = DirectX::XMVector3TransformNormal(defaultUp, matrixRot);	//上方向
	upDirect = DirectX::XMVector3Normalize(upDirect);	//正規化

	DirectX::XMVECTOR rightDirect = DirectX::XMVector3Cross(upDirect, forwardDirect);	//右方向
	rightDirect = DirectX::XMVector3Normalize(rightDirect);	//正規化

	DirectX::XMStoreFloat3(&forward, forwardDirect);
	DirectX::XMStoreFloat3(&up, upDirect);
	DirectX::XMStoreFloat3(&right, rightDirect);

	DirectX::XMVECTOR targetPos = DirectX::XMVectorAdd(cameraPos, forwardDirect);	//ターゲットの位置

	ansVector.at(CAMERA_POS) = cameraPos;
	ansVector.at(TARGET_POS) = targetPos;
	ansVector.at(UP_DIRECT) = upDirect;
	return ansVector;
}

void Camera::UpdateViewMatrix()
{
	std::vector<DirectX::XMVECTOR> viewElement;
	DirectX::XMVECTOR cameraPos, targetPos, upDirect;

	if (p_targetPos == nullptr)
	{
		viewElement = DeriveForwardToTarget();
	}
	else
	{
		viewElement = DeriveTargetToForward();
	}

	cameraPos = viewElement.at(CAMERA_POS);
	targetPos = viewElement.at(TARGET_POS);
	upDirect = viewElement.at(UP_DIRECT);

	matrixView = DirectX::XMMatrixLookAtLH(cameraPos, targetPos, upDirect);	//ビュー行列作成
}

Camera::Camera()
{
	p_targetPos = nullptr;
	fov = 60.0f;
	aspectRatio = 16.0f / 9.0f;
	nearClip = 0.1f;
	farClip = 1000.0f;
}

Camera::Camera(float _fov, float _aspectRatio, float _nearClip, float _farClip)
{
	p_targetPos = nullptr;
	fov = _fov;
	aspectRatio = _aspectRatio;
	nearClip = _nearClip;
	farClip = _farClip;
}

Camera::~Camera()
{}

void Camera::Init()
{
}

void Camera::Update()
{
	UpdateViewMatrix();


}
