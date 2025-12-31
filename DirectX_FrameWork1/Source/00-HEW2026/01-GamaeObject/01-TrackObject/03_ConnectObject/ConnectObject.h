#pragma once
#include "../00-TrackObject/TrackObject.h"

//スプライトレンダラー側にオフセットが無いので、オブジェクトを複数配置変更して管理する


class ConnectObject : public TrackObject
{

public:
	ConnectObject();
	void Init() override;
	void Update() override;
};

