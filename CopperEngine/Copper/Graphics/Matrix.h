#pragma once

#include <cstddef>

namespace cu
{
	template <std::size_t Columns, std::size_t Rows>
	struct Matrix
	{
		float Array[Columns * Rows]{};

		Matrix(const float* rawArray);
	};
}
#include "Matrix.inl"