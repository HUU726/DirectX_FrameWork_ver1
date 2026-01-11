#pragma once
#include "../../../../99-Lib/01-MyLib/998-FH_Types/HF_FLOAT.h"

namespace ThormObjectParam
{
	const char* shadowTexName = "Assets/01-Texture/99-Test/AnimationTestver2.png";
	const char* thormTexName = "Assets/01-Texture/99-Test/daruma.jpg";

	const int  defaultTime = 70;									//通常状態のフレーム数
	const int  fallTime = 50;										//落下状態のフレーム数
	const int  attackTime = 10;										//攻撃状態のフレーム数

	const hft::HFFLOAT3 shadowInitialScale = { 100.f, 100.f, 0.f };	//影の初期の大きさ

	const int thormFallWaitTime = 35;								//トゲが再度落下するまでの待ち時間
	const float thormFallAcceleration = -1.f;						//トゲの落下加速量
	const float distanceHold = 10;									//トゲと影の距離のしきい値
	const float scaleDownSpeed = 1.5;								//落下時の画像の縮小スピード
	const hft::HFFLOAT3 thormIntialOffset = {0.f, 350.f, -10.f};	//影と本体の距離の初期値
	const hft::HFFLOAT3 thormInitialScale = {80.f, 80.f, 0.f};		//トゲのサイズ初期値
}