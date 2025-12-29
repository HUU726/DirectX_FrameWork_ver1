#pragma once
#include "../00-TrackObject/TrackObject.h"

class ConnectObject : public TrackObject
{

public:
	ConnectObject();
	void Init() override;
	void Update() override;
};

