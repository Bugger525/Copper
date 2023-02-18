static const float PI = 3.1415927f;

namespace cu::sys
{
	Angle::Angle(float degrees) : m_Degrees(degrees)
	{
	}
	Angle Angle::Degrees(float degrees)
	{
		return Angle(degrees);
	}
	Angle Angle::Radians(float radians)
	{
		return Angle(radians * (180 / PI));
	}
	float Angle::ToDegrees() const
	{
		return m_Degrees;
	}
	float Angle::ToRadians() const
	{
		return m_Degrees * (PI / 180);
	}
	bool operator==(Angle left, Angle right)
	{
		return left.ToDegrees() == right.ToDegrees();
	}
	bool operator!=(Angle left, Angle right)
	{
		return left.ToDegrees() != right.ToDegrees();
	}
	bool operator<(Angle left, Angle right)
	{
		return left.ToDegrees() < right.ToDegrees();
	}
	bool operator>(Angle left, Angle right)
	{
		return left.ToDegrees() > right.ToDegrees();
	}
	bool operator<=(Angle left, Angle right)
	{
		return left.ToDegrees() <= right.ToDegrees();
	}
	bool operator>=(Angle left, Angle right)
	{
		return left.ToDegrees() >= right.ToDegrees();
	}
	Angle operator-(Angle angle)
	{
		return Angle(-angle.ToDegrees());
	}
	Angle operator-(Angle left, Angle right)
	{
		return Angle(left.ToDegrees() - right.ToDegrees());
	}
	Angle& operator-=(Angle& left, Angle right)
	{
		return left = left - right;
	}
	Angle operator+(Angle left, Angle right)
	{
		return Angle(left.ToDegrees() + right.ToDegrees());
	}
	Angle& operator+=(Angle& left, Angle right)
	{
		return left = left + right;
	}
	Angle operator*(Angle left, float right)
	{
		return Angle(left.ToDegrees() * right);
	}
	Angle operator*(float left, Angle right)
	{
		return Angle(right.ToDegrees() * left);
	}
	Angle& operator*=(Angle& left, float right)
	{
		return left = left * right;
	}
	Angle operator/(Angle left, float right)
	{
		return Angle(left.ToDegrees() / right);
	}
	float operator/(Angle left, Angle right)
	{
		return left.ToDegrees() / right.ToDegrees();
	}
	Angle& operator/=(Angle& left, float right)
	{
		return left = left / right;
	}
}