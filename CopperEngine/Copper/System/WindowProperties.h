#pragma once

#include "Vector2.h"
#include <string>

namespace Copper
{
	struct WindowProperties
	{
		Vector2u Position{};
		Vector2u Size{};
		std::string Title{};

		bool FullScreen{};
		bool Resizable{};

		WindowProperties();
	};
}