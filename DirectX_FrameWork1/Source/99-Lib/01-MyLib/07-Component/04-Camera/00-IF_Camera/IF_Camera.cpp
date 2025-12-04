#include "IF_Camera.h"


/**
* @brief	View行列を更新
*/
void IF_Camera::UpdateViewMatrix()
{
	std::vector<DirectX::XMVECTOR> viewElement;
	DirectX::XMVECTOR cameraPos, targetPos, upDirect;

	if (p_target == nullptr)
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