#pragma once

#include <array>
#include <span>

namespace cu::gfx
{
	template <size_t Columns, size_t Rows>
	struct Matrix
	{
		std::array<float, Columns* Rows> Array;

		Matrix(const std::span<float, Columns* Rows>& arr);
	};
}
#include "Matrix.inl"