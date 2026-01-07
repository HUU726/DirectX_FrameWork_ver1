#pragma once

#include "../00-TrackObject/TrackObject.h"


class TestObject : public TrackObject
{
private:


public:
	TestObject() {}

	void Init() override;
	void Update() override;
};