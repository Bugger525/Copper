#include "AssetStream.h"

#include <fstream>
#include <sstream>
#include "../System/Debug.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace cu::core
{
	AssetStream::AssetStream()
	{
	}
	AssetStream::AssetStream(std::string_view rootDir) : m_RootDir(rootDir)
	{
	}
	std::string_view AssetStream::ReadText(std::string_view path)
	{
		std::string p;
		if (m_RootDir.length() > 0)
		{
			p = m_RootDir;
			p += path;
		}
		else
		{
			p = path;
		}
		std::string text;
		try
		{
			std::ifstream file(p.data());

			std::stringstream stream;
			stream << file.rdbuf();

			file.close();

			text = stream.str();
		}
		catch (std::ifstream::failure e)
		{
			CU_DBG_ERROR("Failed to read shader code: {}", e.what());
			return nullptr;
		}
		return text;
	}
	gfx::Image AssetStream::ReadImage(std::string_view path)
	{
		std::string p;
		if (m_RootDir.length() > 0)
		{
			p = m_RootDir;
			p += path;
		}
		else
		{
			p = path;
		}
		int width, height, nrChannels;
		gfx::Image image;

		unsigned char* data = stbi_load(p.data(), &width, &height, &nrChannels, STBI_rgb_alpha);
		if (!data)
		{
			CU_DBG_ERROR("Failed to load texture: {}", stbi_failure_reason());
		}
		else
		{
			image = gfx::Image(width, height, std::span<unsigned char>(data, width * height * STBI_rgb_alpha));
		}
		stbi_image_free(data);

		return image;
	}
}