#pragma once

#include <random>

class RandGenerator
{
private:
	std::random_device rd;	//乱数精製用変数

	RandGenerator() = default;

public:
	static RandGenerator& GetInstance()
	{
		static RandGenerator instance;
		return instance;
	}

	template<typename T>
	T GetRand(T _start, T _end);

};



/**
* @brief	範囲内でランダムな数値を返す
* @param	T	_start		開始数値
* @param	T	_start		終了数値
* @return	T	ランダムな数値
* @date		2025/09/05
*/
template<typename T>
T RandGenerator::GetRand(T _start, T _end)
{
	std::uniform_int_distribution<T> dist(_start, _end);

	return dist(rd);
}
