#include "Matrix.h"
#include <algorithm>

namespace cu
{
	template <std::size_t Columns, std::size_t Rows>
	Matrix<Columns, Rows>::Matrix(const float* rawArray)
	{
		std::copy(rawArray, rawArray + Columns * Rows, Array);
	}
}