#pragma once

#include <DirectXMath.h>


namespace hft
{
	struct HFFLOAT3;
	struct HFFLOAT4;

	struct HFFLOAT2 : public DirectX::XMFLOAT2
	{
		HFFLOAT2() { x = 0, y = 0; }
		HFFLOAT2(float _value) {x = _value, y = _value; }
		HFFLOAT2(float _x, float _y) { x = _x, y = _y; }
		HFFLOAT2(const HFFLOAT3& _value);

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
		void operator/=(const float& _value);

		bool operator==(const HFFLOAT2& _value);
		bool operator==(const float* rhs) const = delete;
	};

	struct HFFLOAT3 : public DirectX::XMFLOAT3
	{
		HFFLOAT3() { x = 0, y = 0, z = 0; }
		HFFLOAT3(float _x, float _y, float _z) { x = _x, y = _y, z = _z; }
		HFFLOAT3(const HFFLOAT4& _value);

		void operator=(const HFFLOAT2& _value);
		void operator=(const HFFLOAT4& _value);
		HFFLOAT3 operator+(const HFFLOAT3& _value);
		HFFLOAT3 operator+(const HFFLOAT4& _value);
		HFFLOAT3 operator-(const HFFLOAT3& _value);
		HFFLOAT3 operator*(const HFFLOAT3& _value);
		HFFLOAT3 operator/(const HFFLOAT3& _value);
		void operator+=(const HFFLOAT3& _value);
		void operator-=(const HFFLOAT3& _value);
		void operator*=(const HFFLOAT3& _value);
		void operator/=(const HFFLOAT3& _value);
		void operator/=(const float& _value);

		HFFLOAT3 operator*(const float& _value);

	};

	struct HFFLOAT4 : public DirectX::XMFLOAT4
	{
		HFFLOAT4() { x = 0, y = 0, z = 0, w = 0; }
		HFFLOAT4(float _x, float _y, float _z, float _w) { x = _x, y = _y, z = _z, w = _w; }

		void operator=(const HFFLOAT2& _value);
		void operator=(const HFFLOAT3& _value);
		HFFLOAT4 operator+(const HFFLOAT3& _value);
		HFFLOAT4 operator+(const HFFLOAT4& _value);
		HFFLOAT4 operator-(const HFFLOAT4& _value);
		HFFLOAT4 operator*(const HFFLOAT4& _value);
		HFFLOAT4 operator/(const HFFLOAT4& _value);
		void operator+=(const HFFLOAT4& _value);
		void operator-=(const HFFLOAT4& _value);
		void operator*=(const HFFLOAT4& _value);
		void operator/=(const HFFLOAT4& _value);
		void operator/=(const float& _value);

		void operator+=(const HFFLOAT3& _value);
	};
}


