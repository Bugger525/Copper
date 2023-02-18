#include "Matrix.h"

namespace Copper
{
	template <std::size_t Columns, std::size_t Rows>
	Matrix<Columns, Rows>::Matrix(const std::span<float, Columns* Rows>& arr)
	{
		std::copy(arr.begin(), arr.end(), Array.begin());
	}
}