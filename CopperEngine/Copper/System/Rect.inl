#include "Vector2.h"
#include <optional>

// SFML rect

namespace cu::sys
{
	template <typename T>
	Rect<T>::Rect(T x, T y, T width, T height)
		: Position(x, y), Size(width, height)
	{
	}
	template <typename T>
	Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size)
		: Position(position), Size(size)
	{
	}
	template <typename T>
	bool Rect<T>::Contains(T x, T y) const
	{
		const auto Min = [](T a, T b) { return (a < b) ? a : b; };
		const auto Max = [](T a, T b) { return (a < b) ? b : a; };

		const T minX = Min(Position.X, Position.X + Size.X);
		const T maxX = Max(Position.X, Position.X + Size.X);
		const T minY = Min(Position.Y, Position.Y + Size.Y);
		const T maxY = Max(Position.Y, Position.Y + Size.Y);

		return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
	}
	template <typename T>
	bool Rect<T>::Contains(const Vector2<T>& point) const
	{
		const auto Min = [](T a, T b) { return (a < b) ? a : b; };
		const auto Max = [](T a, T b) { return (a < b) ? b : a; };

		const T minX = Min(Position.X, Position.X + Size.X);
		const T maxX = Max(Position.X, Position.X + Size.X);
		const T minY = Min(Position.Y, Position.Y + Size.Y);
		const T maxY = Max(Position.Y, Position.Y + Size.Y);

		return (point.X >= minX) && (point.X < maxX) && (point.Y >= minY) && (point.Y < maxY);
	}
	template <typename T>
	std::optional<Rect<T>> Rect<T>::GetIntersection(const Rect& rect) const
	{
		const auto Min = [](T a, T b) { return (a < b) ? a : b; };
		const auto Max = [](T a, T b) { return (a < b) ? b : a; };

		const T minX1 = Min(Position.X, Position.X + Size.X);
		const T maxX1 = Max(Position.X, Position.X + Size.X);
		const T minY1 = Min(Position.Y, Position.Y + Size.Y);
		const T maxY1 = Max(Position.Y, Position.Y + Size.Y);

		const T minX2 = Min(rect.Position.X, rect.Position.X + rect.Size.X);
		const T maxX2 = Max(rect.Position.X, rect.Position.X + rect.Size.X);
		const T minY2 = Min(rect.Position.Y, rect.Position.Y + rect.Size.Y);
		const T maxY2 = Max(rect.Position.Y, rect.Position.Y + rect.Size.Y);

		const T x = Max(minX1, minX2);
		const T y = Max(minY1, minY2);
		const T width = Min(maxX1, maxX2) - x;
		const T height = Min(maxY1, maxY2) - y;

		if ((x < x + width) && (y < y + height))
		{
			return Rect<T>({ x, y }, { width, height });
		}
		else
		{
			return std::nullopt;
		}
	}
	template <typename T>
	bool Rect<T>::operator==(const Rect& rect)
	{
		return (Position == rect.Position) && (Size == rect.Size);
	}
	template <typename T>
	bool Rect<T>::operator!=(const Rect& rect)
	{
		return (Position != rect.Position) || (Size != rect.Size);
	}
	template struct Rect<int>;
	template struct Rect<float>;
}