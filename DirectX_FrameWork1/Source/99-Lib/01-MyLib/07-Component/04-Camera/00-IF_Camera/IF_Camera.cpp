#include "IF_Camera.h"



void IF_Camera::UpdateViewMatrix()
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

	matrixView = DirectX::XMMatrixLookAtLH(cameraPos, targetPos, upDirect);	//ÉrÉÖÅ[çsóÒçÏê¨
}