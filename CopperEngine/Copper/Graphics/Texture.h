#pragma once

#include <string>
#include <span>
#include <vector>

namespace cu
{
	class Texture
	{
	private:
		unsigned int m_Data;

		unsigned int m_Width;
		unsigned int m_Height;

		std::vector<unsigned char> m_Image;
	public:
		Texture();
		Texture(unsigned int width, unsigned int height, std::span<unsigned char> image);
		~Texture();

		void Use() const;

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		const std::vector<unsigned char>& GetImage() const;

		void Cleanup();
	};
}