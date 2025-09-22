#include "Time.h"


Time::Time()
{
	fps = 60.f;
	spf = std::chrono::microseconds(static_cast<int>((1.f / fps) * 1'000'000));
	curTime = std::chrono::high_resolution_clock::now();
}

void Time::SetFps(float _fps)
{
	fps = _fps;
	spf = std::chrono::microseconds(static_cast<int>((1.f / fps) * 1'000'000));
}

std::chrono::steady_clock::time_point Time::NowTimeMicro()
{
	return std::chrono::high_resolution_clock::now();
}

float Time::NowTimeSecond()
{
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> seconds = now.time_since_epoch();
	float floatNowTime = seconds.count();
	return floatNowTime;
}

float Time::DeltaTime()
{
	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - preTime);	//経過時間
	float deltaTime = elapsedTime.count() / 1000000.0f;
	return deltaTime;
}

bool Time::Update()
{
	auto nowTime = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(nowTime - curTime);	//経過時間
	if (spf > elapsedTime)
		return true;		//１フレーム未満

	preTime = curTime;
	curTime = std::chrono::high_resolution_clock::now();
	return false;	//１フレームを超えている
}
