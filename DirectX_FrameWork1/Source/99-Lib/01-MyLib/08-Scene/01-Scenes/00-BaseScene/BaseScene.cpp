#include "BaseScene.h"

#include "../../../06-GameObject/999-GameObjectManager/GameObjectManager.h"

BaseScene::BaseScene()
{
	GameObjectManager::GetInstance().ClearWaitingQueue();
}
