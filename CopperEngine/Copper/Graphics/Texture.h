#pragma once

#include <string>

namespace cu
{
	class Texture
	{
	private:
		unsigned int m_Data;

		unsigned int m_Width;
		unsigned int m_Height;
	public:
		Texture();
		Texture(unsigned int width, unsigned int height, unsigned char* const image);
		~Texture();

		void Use() const;

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		void Cleanup();
	};
}