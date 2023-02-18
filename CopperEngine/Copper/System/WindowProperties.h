#pragma once

#include "Vector2.h"
#include <string>

namespace cu::sys
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