#pragma once

namespace cu::sys
{
	template <typename T>
	struct Vector3
	{
		T X{}, Y{}, Z{};

		Vector3();
		Vector3(T x, T y, T z);
		Vector3(const Vector3& copy);

		T Length() const;
		T LengthSquared() const;
		Vector3 Normalized() const;
		float Dot(const Vector3& vec);
	};
	using Vector3f = Vector3<float>;
	using Vector3i = Vector3<int>;

	template <typename T>
	Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right);
	template <typename T>
	Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right);

	template <typename T>
	Vector3<T> operator-(const Vector3<T>& vec);
	template <typename T>
	Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right);
	template <typename T>
	Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right);

	template <typename T>
	Vector3<T> operator*(const Vector3<T>& left, T scale);
	template <typename T>
	Vector3<T> operator*(T scale, const Vector3<T>& right);
	template <typename T>
	Vector3<T>& operator*=(Vector3<T>& left, T scale);

	template <typename T>
	Vector3<T> operator/(const Vector3<T>& left, T scale);
	template <typename T>
	Vector3<T>& operator/=(Vector3<T>& left, T scale);

	template <typename T>
	bool operator==(const Vector3<T>& left, const Vector3<T>& right);
	template <typename T>
	bool operator!=(const Vector3<T>& left, const Vector3<T>& right);
}
#include "Vector3.inl"