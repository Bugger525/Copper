#pragma once

namespace Copper
{
	template <typename T>
	struct Vector4
	{
		T X{}, Y{}, Z{}, W{};

		Vector4(T x, T y, T z, T w);
	};
	using Vector4f = Vector4<float>;
	using Vector4i = Vector4<int>;
}
#include "Vector4.inl"