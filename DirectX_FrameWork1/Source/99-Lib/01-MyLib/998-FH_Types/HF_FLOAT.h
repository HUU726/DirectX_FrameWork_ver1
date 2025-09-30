#pragma once

#include <DirectXMath.h>


namespace hft
{
	struct HFFLOAT3;
	struct HFFLOAT4;

	struct HFFLOAT2 : public DirectX::XMFLOAT2
	{
		HFFLOAT2() { x = 0, y = 0; }
		HFFLOAT2(float _x, float _y) { x = _x, y = _y; }

		void operator=(const HFFLOAT2& _value);
		void operator=(const HFFLOAT3& _value);
		void operator=(const HFFLOAT4& _value);
		HFFLOAT2 operator+(const HFFLOAT2& _value);
		HFFLOAT2 operator-(const HFFLOAT2& _value);
		HFFLOAT2 operator*(const HFFLOAT2& _value);
		HFFLOAT2 operator/(const HFFLOAT2& _value);
		void operator+=(const HFFLOAT2& _value);
		void operator-=(const HFFLOAT2& _value);
		void operator*=(const HFFLOAT2& _value);
		void operator/=(const HFFLOAT2& _value);
	};

	struct HFFLOAT3 : public DirectX::XMFLOAT3
	{
		HFFLOAT3() { x = 0, y = 0, z = 0; }
		HFFLOAT3(float _x, float _y, float _z) { x = _x, y = _y, z = _z; }
		HFFLOAT3(const HFFLOAT4& _value);

		void operator=(const HFFLOAT2& _value);
		void operator=(const HFFLOAT4& _value);
		HFFLOAT3 operator+(const HFFLOAT3& _value);
		HFFLOAT3 operator-(const HFFLOAT3& _value);
		HFFLOAT3 operator*(const HFFLOAT3& _value);
		HFFLOAT3 operator/(const HFFLOAT3& _value);
		void operator+=(const HFFLOAT3& _value);
		void operator-=(const HFFLOAT3& _value);
		void operator*=(const HFFLOAT3& _value);
		void operator/=(const HFFLOAT3& _value);
	};

	struct HFFLOAT4 : public DirectX::XMFLOAT4
	{
		HFFLOAT4() { x = 0, y = 0, z = 0, w = 0; }
		HFFLOAT4(float _x, float _y, float _z, float _w) { x = _x, y = _y, z = _z, w = _w; }

		void operator=(const HFFLOAT2& _value);
		void operator=(const HFFLOAT3& _value);
		HFFLOAT4 operator+(const HFFLOAT4& _value);
		HFFLOAT4 operator-(const HFFLOAT4& _value);
		HFFLOAT4 operator*(const HFFLOAT4& _value);
		HFFLOAT4 operator/(const HFFLOAT4& _value);
		void operator+=(const HFFLOAT4& _value);
		void operator-=(const HFFLOAT4& _value);
		void operator*=(const HFFLOAT4& _value);
		void operator/=(const HFFLOAT4& _value);
	};
}



void operator==(DirectX::XMFLOAT3& _value1, const DirectX::XMFLOAT4& _value2)
{
	_value1 = { _value2.x,_value2.y,_value2.y };
}



DirectX::XMFLOAT2 operator+(const DirectX::XMFLOAT2& _value1, const DirectX::XMFLOAT2& _value2)
{
	return { _value1.x + _value2.x,_value1.y + _value2.y };
}
DirectX::XMFLOAT2 operator-(const DirectX::XMFLOAT2& _value1, const DirectX::XMFLOAT2& _value2)
{
	return { _value1.x - _value2.x,_value1.y - _value2.y };
}
DirectX::XMFLOAT2 operator*(const DirectX::XMFLOAT2& _value1, const DirectX::XMFLOAT2& _value2)
{
	return { _value1.x * _value2.x,_value1.y * _value2.y };
}
DirectX::XMFLOAT2 operator/(const DirectX::XMFLOAT2& _value1, const DirectX::XMFLOAT2& _value2)
{
	return { _value1.x / _value2.x,_value1.y / _value2.y };
}

void operator+=(DirectX::XMFLOAT2& _value1, const DirectX::XMFLOAT2& _value2)
{
	_value1.x += _value2.x;
	_value1.y += _value2.y;
}
void operator-=(DirectX::XMFLOAT2& _value1, const DirectX::XMFLOAT2& _value2)
{
	_value1.x -= _value2.x;
	_value1.y -= _value2.y;
}
void operator*=(DirectX::XMFLOAT2& _value1, const DirectX::XMFLOAT2& _value2)
{
	_value1.x *= _value2.x;
	_value1.y *= _value2.y;
}
void operator/=(DirectX::XMFLOAT2& _value1, const DirectX::XMFLOAT2& _value2)
{
	_value1.x /= _value2.x;
	_value1.y /= _value2.y;
}