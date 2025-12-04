#include "Vector.h"


namespace hft
{
	//Dotê»ÇÃã§í é¿ëï
	template<>
	inline float Vector<HFFLOAT2>::Dot(const Vector& _vec) const
	{
		return { x * _vec.x + y * _vec.y };
	}

	template<>
	inline float Vector<HFFLOAT3>::Dot(const Vector& _vec) const
	{
		return { x * _vec.x + y * _vec.y + z * _vec.z };
	}

	template<>
	inline float Vector<HFFLOAT4>::Dot(const Vector& _vec) const
	{
		return { x * _vec.x + y * _vec.y + z * _vec.z + w * _vec.w };
	}




	//CrossêœÇÃã§í é¿ëï
	template<>
	inline Vector<HFFLOAT2> Vector<HFFLOAT2>::Cross(const Vector& _vec) const
	{
		return HFFLOAT2{ x * _vec.y - y * _vec.x,0.0f };
	}

	template<>
	inline Vector<HFFLOAT3> Vector<HFFLOAT3>::Cross(const Vector& _vec) const
	{
		return HFFLOAT3{
			y * _vec.z - z * _vec.y,
			z * _vec.x - x * _vec.z,
			x * _vec.y - y * _vec.x
		};
	}

	template<>
	inline Vector<HFFLOAT4> Vector<HFFLOAT4>::Cross(const Vector& _vec) const
	{
		return HFFLOAT4{
			y * _vec.z - z * _vec.y,
			z * _vec.x - x * _vec.z,
			x * _vec.y - y * _vec.x,
			0
		};
	}

	inline Vector3 Vector3::Transform(const Vector3& _vec, const DirectX::XMMATRIX& _mat) noexcept
	{
		DirectX::XMVECTOR v1 = DirectX::XMLoadFloat3(&_vec);
		DirectX::XMVECTOR X = DirectX::XMVector3TransformCoord(v1, _mat);

		Vector3 result;
		DirectX::XMStoreFloat3(&result, X);
		return result;
	}

	HFFLOAT3 Vector3::Transform(const HFFLOAT3& _value, const DirectX::XMMATRIX& _mat) noexcept
	{
		DirectX::XMVECTOR v1 = DirectX::XMLoadFloat3(&_value);
		DirectX::XMVECTOR X = DirectX::XMVector3TransformCoord(v1, _mat);

		Vector3 result;
		DirectX::XMStoreFloat3(&result, X);
		return result;
	}


	float Dot(HFFLOAT3 _vec1, HFFLOAT3 _vec2)
	{
		return (_vec1.x * _vec2.x + _vec1.y * _vec2.y + _vec1.z * _vec2.z);
	}

	HFFLOAT3 Cross(HFFLOAT3 _vec1, HFFLOAT3 _vec2)
	{
		return { _vec1.y * _vec2.z - _vec1.z * _vec2.y,
				_vec1.z * _vec2.x - _vec1.x * _vec2.z,
				_vec1.x * _vec2.y - _vec1.y * _vec2.x };
	}

}