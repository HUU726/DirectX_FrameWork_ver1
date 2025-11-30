#include "Camera3D.h"

#include "../../99-CompMng/ComponentManager.h"
#include "../../../02-Renderer/02-Mesh3DRenderer/Mesh3DRenderer.h"
#include "../../../06-GameObject/GameObject.h"
#include "../../../../../02-App/HF_Window.h"


std::vector<DirectX::XMVECTOR> Camera3D::DeriveTargetToForward()
{
	std::vector<DirectX::XMVECTOR> ansVector;
	ansVector.resize(ALL_ELEMENT);

	DirectX::XMVECTOR cameraPos, targetPos;

	{
		Transform l_transform = GetGameObject()->GetTransform();
		auto pos = l_transform.position;
		cameraPos = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.f);		//カメラの位置
	}

	{
		auto pos = p_target->GetTransform().position;
		targetPos = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.f);	//ターゲットの位置
	}

	DirectX::XMVECTOR defaultUp = DirectX::XMVectorSet(0.f,1.f,0.f,0.f);	//ワールドの上方向
	

	auto forwardDirect = DirectX::XMVectorSubtract(targetPos, cameraPos);	//前方向
	forwardDirect = DirectX::XMVector3Normalize(forwardDirect);	//正規化

	auto rightDirect = DirectX::XMVector3Cross(defaultUp, forwardDirect);	//右方向
	rightDirect = DirectX::XMVector3Normalize(rightDirect);	//正規化

	auto upDirect = DirectX::XMVector3Cross(forwardDirect, rightDirect);	//上方向
	upDirect = DirectX::XMVector3Normalize(upDirect);	//正規化

	DirectX::XMStoreFloat3(&forward, forwardDirect);
	DirectX::XMStoreFloat3(&up, upDirect);
	DirectX::XMStoreFloat3(&right, rightDirect);

	ansVector.at(CAMERA_POS) = cameraPos;
	ansVector.at(TARGET_POS) = targetPos;
	ansVector.at(UP_DIRECT) = upDirect;

	return ansVector;
}

std::vector<DirectX::XMVECTOR> Camera3D::DeriveForwardToTarget()
{
	std::vector<DirectX::XMVECTOR> ansVector;
	ansVector.resize(ALL_ELEMENT);

	Transform l_transform = GetGameObject()->GetTransform();
	auto pos = l_transform.position;
	auto rot = l_transform.rotation;
	DirectX::XMVECTOR cameraPos = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);		//カメラの位置

	DirectX::XMVECTOR defaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);	//初期前方向
	DirectX::XMVECTOR defaultUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);			//初期上方向
	
	rot.x = DirectX::XMConvertToRadians(rot.x);
	rot.y = DirectX::XMConvertToRadians(rot.y);
	rot.z = DirectX::XMConvertToRadians(rot.z);
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

Camera3D::Camera3D()
{
	p_target = nullptr;
	fov = 60.0f;
	aspect = static_cast<float>SCREEN_WIDTH / static_cast<float>SCREEN_HEIGHT;
	nearClip = 0.1f;
	farClip = 100000.0f;
	forward = { 0.f,0.f,1.f };
	right = { 1.f,0.f,0.f };
	up = { 0.f,1.f,0.f };

	ComponentManager<Camera3D>::GetInstance().Add(this);
}

Camera3D::Camera3D(float _fov, float _aspectRatio, float _nearClip, float _farClip)
{
	p_target = nullptr;
	fov = _fov;
	aspect = _aspectRatio;
	nearClip = _nearClip;
	farClip = _farClip;
	forward = { 0.f,0.f,1.f };
	right = { 1.f,0.f,0.f };
	up = { 0.f,1.f,0.f };

	auto& compMng = ComponentManager<Camera3D>::GetInstance();
	compMng.Add(this);
	compMng.SetType(COMP_MNG_TYPES::COMP_CAMERA3D);
}

Camera3D::~Camera3D()
{
	ComponentManager<Camera3D>::GetInstance().Remove(this);
}

void Camera3D::Init()
{
	matrixProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fov), aspect, nearClip, farClip);	//プロジェクション行列作成
	UpdateViewMatrix();	//ビュー行列更新
}

void Camera3D::Update()
{
	UpdateViewMatrix();
	Mesh3DRenderer::GetInstance().SetVPMatrix();
}

void Camera3D::Action()
{
	Update();
}
