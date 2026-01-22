#include "HewTestGameObject.h"

#include <Windows.h>

#include "../../20-Scene/Test_HewScene.h"
#include "../../20-Scene/Test_HewScene2.h"

#include "../../../99-Lib/01-MyLib/08-Scene/02-SceneManager/SceneManager.h"
void ObjectS1::Init()
{

}

void ObjectS1::Update()
{
	if (GetAsyncKeyState(VK_UP) & 0x0001)
		SceneManager::GetInstance().LoadScene<Test_HewScene2>();
}


void ObjectS2::Init()
{

}

void ObjectS2::Update()
{
	if (GetAsyncKeyState(VK_UP) & 0x0001)
		SceneManager::GetInstance().LoadScene<Test_HewScene>();
}