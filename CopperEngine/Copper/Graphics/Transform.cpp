#include "Transform.h"
#include <algorithm>

namespace Copper
{
	Transform::Transform()
	{
		m_Data =
		{
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}
	const std::array<float, 16>& Transform::GetData() const
	{
		return m_Data;
	}
	void Transform::Translate(const Vector2f& vec)
	{
		for (size_t i = 0; i < 4; i++)
		{
			m_Data[i + 4 * 3] = (m_Data[i] * vec.X
				+ m_Data[i + 4 * 1] * vec.Y
				+ m_Data[i + 4 * 2] * 0
				+ m_Data[i + 4 * 3]);
		}
	}
	void Transform::Scale(const Vector2f& scale)
	{
		for (size_t i = 0; i < 4; i++)
		{
			m_Data[i] *= scale.X;
			m_Data[i + 4 * 1] *= scale.Y;
			m_Data[i + 4 * 2] *= 1;
		}
	}
	void Transform::Rotate(Angle angle)
	{
		float rad = angle.ToRadians();
		float cos = std::cos(rad);
		float sin = std::cos(rad);
	}
	void Transform::ToMatrix(Matrix<3, 3>& mat)
	{
		auto to = mat.Array;

		to[0] = m_Data[0];
		to[1] = m_Data[1];
		to[2] = m_Data[3];
		to[3] = m_Data[4];
		to[4] = m_Data[5];
		to[5] = m_Data[7];
		to[6] = m_Data[12];
		to[7] = m_Data[13];
		to[8] = m_Data[15];
	}
	void Transform::ToMatrix(Matrix<4, 4>& mat)
	{
		mat.Array = m_Data;
	}
}