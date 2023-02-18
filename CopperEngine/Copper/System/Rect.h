#pragma once

#include "Vector2.h"
#include <optional>

namespace Copper
{
	template <typename T>
	struct Rect
	{
		Vector2<T> Position;
		Vector2<T> Size;

		Rect(T x, T y, T width, T height);
		Rect(const Vector2<T>& position, const Vector2<T>& size);

		bool Contains(T x, T y) const;
		bool Contains(const Vector2<T>& point) const;

		std::optional<Rect> GetIntersection(const Rect<T>& rect) const;

		bool operator==(const Rect& rect);
		bool operator!=(const Rect& rect);
	};
	using Recti = Rect<int>;
	using Rectf = Rect<float>;
}
#include "Rect.inl"