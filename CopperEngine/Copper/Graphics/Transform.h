#pragma once

#include "Matrix.h"
#include "../System/Angle.h"
#include "../System/Vector2.h"

namespace cu
{
	class Transform
	{
	private:
		float* m_Data;
	public:
		Transform();
		~Transform();

		const float* GetData() const;

		void Translate(const Vector2f& vec);
		void Scale(const Vector2f& scale);
		void Rotate(Angle angle);

		void ToMatrix(Matrix<4, 4>& mat);
		void ToMatrix(Matrix<3, 3>& mat);
	};
}