#pragma once

#include "./HF_FLOAT.h"
#include <cmath>
#include <algorithm>


namespace hft
{
	template<class T>
	struct Vector : public T
	{
		using Base = T;
		using Self = Vector<T>;

		Vector() = default;
		Vector(const T& _vec) : T(_vec) {}

		Self Cross(const Self& _vec) const;
		float Dot(const Self& _vec) const;
		float AngleRad(const Self& _vec) const
		{
			float dot = Dot(_vec);
			float len1 = Lenght();
			float len2 = _vec.Lenght();

			if ( len1 == 0.0f || len2 == 0.0f ) return 0.0f;

			float cosTheta = dot / (len1 * len2);

			//êîílåÎç∑ëŒçÙ (-1~1Ç…ÉNÉâÉìÉv)
			cosTheta = std::clamp(cosTheta, -1.0f, 1.0f);

			return std::acos(cosTheta);
		}
		float AngleDeg(const Vector& _vec) const
		{
			constexpr float radToDeg = 180.0f / float(DirectX::XM_PI);
			return AngleRad(_vec) * radToDeg;
		}
		float Lenght() const { return std::sqrt(Dot(*this)); }
		Self Normalize() const
		{
			float len = Lenght();
			Self result = *this;
			result /= len;
			return result;
		}

		
	};


	struct Vector2 : public Vector<HFFLOAT2>
	{

	};

	struct Vector3 : public Vector<HFFLOAT3>
	{
		static Vector3 Transform(const Vector3& _vec, const DirectX::XMMATRIX& _mat) noexcept;
		static HFFLOAT3 Transform(const HFFLOAT3& _value, const DirectX::XMMATRIX& _mat) noexcept;
	};

	struct Vector4 : public Vector<HFFLOAT4>
	{

	};

	float Dot(HFFLOAT3 _vec1, HFFLOAT3 _vec2);
	HFFLOAT3 Cross(HFFLOAT3 _vec1, HFFLOAT3 _vec2);
}