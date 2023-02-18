#pragma once

#include "Matrix.h"
#include "../System/Angle.h"
#include "../System/Vector2.h"
#include <array>

namespace cu::gfx
{
	class Transform
	{
	private:
		std::array<float, 16> m_Data;
	public:
		Transform();

		const std::array<float, 16>& GetData() const;

		void Translate(const Vector2f& vec);
		void Scale(const Vector2f& scale);
		void Rotate(Angle angle);

		void ToMatrix(Matrix<4, 4>& mat);
		void ToMatrix(Matrix<3, 3>& mat);
	};
}