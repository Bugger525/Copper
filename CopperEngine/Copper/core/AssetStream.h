#pragma once

#include <string>
#include "../Graphics/Image.h"

namespace Copper
{
	class AssetStream
	{
	private:
		std::string m_RootDir;
	public:
		AssetStream();
		AssetStream(std::string_view rootDir);

		std::string_view ReadText(std::string_view path);
		gfx::Image ReadImage(std::string_view path);
	};
}