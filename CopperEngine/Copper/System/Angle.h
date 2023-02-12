#pragma once

namespace cu
{
	class Angle
	{
	private:
		float m_Degrees;
	public:
		inline Angle(float degrees);

		inline static Angle Degrees(float degrees);
		inline static Angle Radians(float radians);

		inline float ToDegrees() const;
		inline float ToRadians() const;
	};

	inline bool operator==(Angle left, Angle right);
	inline bool operator!=(Angle left, Angle right);

	inline bool operator<(Angle left, Angle right);
	inline bool operator>(Angle left, Angle right);
	inline bool operator<=(Angle left, Angle right);
	inline bool operator>=(Angle left, Angle right);

	inline Angle operator-(Angle angle);
	inline Angle operator-(Angle left, Angle right);
	inline Angle& operator-=(Angle& left, Angle right);

	inline Angle operator+(Angle left, Angle right);
	inline Angle& operator+=(Angle& left, Angle right);

	inline Angle operator*(Angle left, float right);
	inline Angle operator*(float left, Angle right);
	inline Angle& operator*=(Angle& left, float right);

	inline Angle operator/(Angle left, float right);
	inline float operator/(Angle left, Angle right);
	inline Angle& operator/=(Angle& left, float right);
}
#include "Angle.inl"