#include "HF_FLOAT.h"


/********************************************************************************************
* HFFLOAT2
********************************************************************************************/
void hft::HFFLOAT2::operator=(const HFFLOAT3& _value)
{
	this->x = _value.x;
	this->y = _value.y;
}

void hft::HFFLOAT2::operator=(const HFFLOAT4& _value)
{
	this->x = _value.x;
	this->y = _value.y;
}

hft::HFFLOAT2 hft::HFFLOAT2::operator+(const HFFLOAT2& _value)
{
	return { x + _value.x,y + _value.y };
}

hft::HFFLOAT2 hft::HFFLOAT2::operator-(const HFFLOAT2& _value)
{
	return { x - _value.x,y - _value.y };
}

hft::HFFLOAT2 hft::HFFLOAT2::operator*(const HFFLOAT2& _value)
{
	return { x * _value.x,y * _value.y };
}

hft::HFFLOAT2 hft::HFFLOAT2::operator/(const HFFLOAT2& _value)
{
	return { x / _value.x,y / _value.y };
}

void hft::HFFLOAT2::operator+=(const HFFLOAT2& _value)
{
	x += _value.x;
	y += _value.y;
}

void hft::HFFLOAT2::operator-=(const HFFLOAT2& _value)
{
	x -= _value.x;
	y -= _value.y;
}

void hft::HFFLOAT2::operator*=(const HFFLOAT2& _value)
{
	x *= _value.x;
	y *= _value.y;
}

void hft::HFFLOAT2::operator/=(const HFFLOAT2& _value)
{
	x /= _value.x;
	y /= _value.y;
}

bool hft::HFFLOAT2::operator==(const HFFLOAT2& _value)
{
	return (x == _value.x && y == _value.y);
}


/********************************************************************************************
* HFFLOAT3
********************************************************************************************/
hft::HFFLOAT3::HFFLOAT3(const HFFLOAT4& _value)
{
	x = _value.x;
	y = _value.y;
	z = _value.z;
}

void hft::HFFLOAT3::operator=(const HFFLOAT2& _value)
{
	x = _value.x;
	y = _value.y;
	z = 0.f;
}
void hft::HFFLOAT3::operator=(const HFFLOAT4& _value)
{
	x = _value.x;
	y = _value.y;
	z = _value.z;
}
hft::HFFLOAT3 hft::HFFLOAT3::operator+(const HFFLOAT3& _value)
{
	return { x + _value.x,y + _value.y,z + _value.z };
}
hft::HFFLOAT3 hft::HFFLOAT3::operator-(const HFFLOAT3& _value)
{
	return { x - _value.x,y - _value.y,z - _value.z };
}
hft::HFFLOAT3 hft::HFFLOAT3::operator*(const HFFLOAT3& _value)
{
	return { x * _value.x,y * _value.y,z * _value.z };
}
hft::HFFLOAT3 hft::HFFLOAT3::operator/(const HFFLOAT3& _value)
{
	return { x / _value.x,y / _value.y,z / _value.z };
}
void hft::HFFLOAT3::operator+=(const HFFLOAT3& _value)
{
	x += _value.x;
	y += _value.y;
	z += _value.z;
}
void hft::HFFLOAT3::operator-=(const HFFLOAT3& _value)
{
	x -= _value.x;
	y -= _value.y;
	z -= _value.z;
}
void hft::HFFLOAT3::operator*=(const HFFLOAT3& _value)
{
	x *= _value.x;
	y *= _value.y;
	z *= _value.z;
}
void hft::HFFLOAT3::operator/=(const HFFLOAT3& _value)
{
	x /= _value.x;
	y /= _value.y;
	z /= _value.z;
}

hft::HFFLOAT3 hft::HFFLOAT3::operator*(const float& _value)
{
    return { x * _value, y * _value, z * _value };
}


/********************************************************************************************
* HFFLOAT4
********************************************************************************************/
void hft::HFFLOAT4::operator=(const HFFLOAT2& _value)
{
	x = _value.x;
	y = _value.y;
	z = 0.f;
	w = 0.f;
}
void hft::HFFLOAT4::operator=(const HFFLOAT3& _value)
{
	x = _value.x;
	y = _value.y;
	z = _value.z;
	w = 0.f;
}
hft::HFFLOAT4 hft::HFFLOAT4::operator+(const HFFLOAT4& _value)
{
	return { x + _value.x,y + _value.y,z + _value.z,w + _value.w };
}
hft::HFFLOAT4 hft::HFFLOAT4::operator-(const HFFLOAT4& _value)
{
	return { x - _value.x,y - _value.y,z - _value.z,w - _value.w };
}
hft::HFFLOAT4 hft::HFFLOAT4::operator*(const HFFLOAT4& _value)
{
	return { x * _value.x,y * _value.y,z * _value.z,w * _value.w };
}
hft::HFFLOAT4 hft::HFFLOAT4::operator/(const HFFLOAT4& _value)
{
	return { x / _value.x,y / _value.y,z / _value.z,w / _value.w };
}
void hft::HFFLOAT4::operator+=(const HFFLOAT4& _value)
{
	x += _value.x;
	y += _value.y;
	z += _value.z;
	w += _value.w;
}
void hft::HFFLOAT4::operator-=(const HFFLOAT4& _value)
{
	x -= _value.x;
	y -= _value.y;
	z -= _value.z;
	w -= _value.w;
}
void hft::HFFLOAT4::operator*=(const HFFLOAT4& _value)
{
	x *= _value.x;
	y *= _value.y;
	z *= _value.z;
	w *= _value.w;
}
void hft::HFFLOAT4::operator/=(const HFFLOAT4& _value)
{
	x /= _value.x;
	y /= _value.y;
	z /= _value.z;
	w /= _value.w;
}

void hft::HFFLOAT4::operator+=(const hft::HFFLOAT3& _value)
{
	x += _value.x;
	y += _value.y;
	z += _value.z;
}