#pragma once
#include "../00-TrackObject/TrackObject.h"

//朝日奈担当連結オブジェクトクラス

//スプライトレンダラー側にオフセットが無いので、連結部分の描画はオブジェクトを複数配置変更して管理する

//検知用の当たり判定の長さ（縦横の半径）
//検知用のコライダー縦横2つ

class ConnectObject : public TrackObject
{
private:
	



public:
	ConnectObject();
	void Init() override;
	void Update() override;
};

