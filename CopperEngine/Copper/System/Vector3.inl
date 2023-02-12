#include <cmath>

namespace cu
{
	template <typename T>
	Vector3<T>::Vector3() { }
	template <typename T>
	Vector3<T>::Vector3(T x, T y, T z) : X(x), Y(y), Z(z)
	{
	}
	template <typename T>
	Vector3<T>::Vector3(const Vector3& copy) : X(copy.X), Y(copy.Y), Z(copy.Z)
	{
	}
	template <typename T>
	T Vector3<T>::Length() const
	{
		return std::sqrt(X * X + Y * Y + Z * Z);
	}
	template <typename T>
	T Vector3<T>::LengthSquared() const
	{
		return X * X + Y * Y + Z * Z;
	}
	template <typename T>
	Vector3<T> Vector3<T>::Normalized() const
	{
		return (*this) / Length();
	}
	template <typename T>
	float Vector3<T>::Dot(const Vector3& vec)
	{
		return X * vec.X + Y * vec.Y + Z * vec.Z;
	}
	template<typename T>
	Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
	{
		return Vector3(left.X + right.X, left.Y + right.Y, left.Z + right.Z);
	}
	template<typename T>
	Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right)
	{
		left.X += right.X;
		left.Y += right.Y;
		left.Z += right.Z;
	}
	template<typename T>
	Vector3<T> operator-(const Vector3<T>& vec)
	{
		return Vector3(-vec.X, -vec.Y, -vec.Z);
	}
	template<typename T>
	Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right)
	{
		return Vector3(left.X - right.X, left.Y - right.Y, left.Z - right.Z);
	}
	template<typename T>
	Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right)
	{
		left.X -= right.X;
		left.Y -= right.Y;
		left.Z -= right.Z;
	}
	template<typename T>
	Vector3<T> operator*(const Vector3<T>& left, T scale)
	{
		return Vector3(left.X * scale, left.Y * scale, left.Z * scale);
	}
	template<typename T>
	Vector3<T> operator*(T scale, const Vector3<T>& right)
	{
		return Vector3(right.X * scale, right.Y * scale, right.Z * scale);
	}
	template<typename T>
	Vector3<T>& operator*=(Vector3<T>& left, T scale)
	{
		left.X *= scale;
		left.Y *= scale;
		left.Z *= scale;

		return left;
	}
	template<typename T>
	Vector3<T> operator/(const Vector3<T>& left, T scale)
	{
		return Vector3(left.X / scale, left.Y / scale, left.Z / scale);
	}
	template<typename T>
	Vector3<T>& operator/=(Vector3<T>& left, T scale)
	{
		left.X /= scale;
		left.Y /= scale;
		left.Z /= scale;

		return left;
	}
	template<typename T>
	bool operator==(const Vector3<T>& left, const Vector3<T>& right)
	{
		return (left.X == right.X) && (left.Y == right.Y) && (left.Z == right.Z);
	}
	template<typename T>
	bool operator!=(const Vector3<T>& left, const Vector3<T>& right)
	{
		return (left.X != right.X) || (left.Y != right.Y) || (left.Z != right.Z);
	}
}