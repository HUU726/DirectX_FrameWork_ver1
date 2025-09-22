#pragma once

#include <chrono>
class Time
{
private:
	float fps;	// フレーム／秒
	std::chrono::microseconds spf;	// 秒／フレーム	
	std::chrono::steady_clock::time_point curTime;	//フレーム開始時間
	std::chrono::steady_clock::time_point preTime;

	Time();

public:
	static Time& GetInstance()
	{
		static Time instance;
		return instance;
	}
	
	void SetFps(float _fps);
	std::chrono::steady_clock::time_point NowTimeMicro();
	float NowTimeSecond();
	float DeltaTime();

	bool Update();

};

